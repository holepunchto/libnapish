#include <assert.h>
#include <bare.h>
#include <js.h>

static js_value_t *
addon_exports(js_env_t *env, js_value_t *exports) {
  int err = js_create_string_utf8(env, (utf8_t *) "Hello from addon", -1, &exports);
  assert(err == 0);

  return exports;
}

__attribute__((constructor)) static void
addon_register(void) {
  bare_module_t module = {0, "addon", addon_exports};

  bare_module_register(&module);
}
