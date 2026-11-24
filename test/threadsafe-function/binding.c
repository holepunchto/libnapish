#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdbool.h>

static int context;
static int finalize_hint;
static int data;

static js_ref_t *callback;

static void
addon_report(js_env_t *env, const char *event, bool matches) {
  int err;

  js_value_t *argv[2];

  err = js_create_string_utf8(env, (utf8_t *) event, -1, &argv[0]);
  assert(err == 0);

  err = js_get_boolean(env, matches, &argv[1]);
  assert(err == 0);

  js_value_t *function;
  err = js_get_reference_value(env, callback, &function);
  assert(err == 0);

  js_value_t *receiver;
  err = js_get_global(env, &receiver);
  assert(err == 0);

  err = js_call_function(env, receiver, function, 2, argv, NULL);
  assert(err == 0);
}

static void
addon_on_call(js_env_t *env, js_value_t *function, void *call_context, void *call_data) {
  addon_report(env, "call", call_context == &context && call_data == &data);
}

static void
addon_on_finalize(js_env_t *env, void *finalize_data, void *hint) {
  addon_report(env, "finalize", finalize_data == &context && hint == &finalize_hint);

  int err = js_delete_reference(env, callback);
  assert(err == 0);
}

static js_value_t *
addon_run(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];
  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  err = js_create_reference(env, argv[0], 1, &callback);
  assert(err == 0);

  js_threadsafe_function_t *function;
  err = js_create_threadsafe_function(env, NULL, 0, 1, addon_on_finalize, &finalize_hint, &context, addon_on_call, &function);
  assert(err == 0);

  void *result;
  err = js_get_threadsafe_function_context(function, &result);
  assert(err == 0);

  addon_report(env, "context", result == &context);

  err = js_call_threadsafe_function(function, &data, js_threadsafe_function_nonblocking);
  assert(err == 0);

  err = js_release_threadsafe_function(function, js_threadsafe_function_release);
  assert(err == 0);

  return NULL;
}

static js_value_t *
addon_exports(js_env_t *env, js_value_t *exports) {
  js_value_t *function;
  int err = js_create_function(env, "run", -1, addon_run, NULL, &function);
  assert(err == 0);

  return function;
}

BARE_MODULE(addon, addon_exports)
