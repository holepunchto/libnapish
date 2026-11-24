#ifndef JS_H
#define JS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <utf.h>

typedef struct uv_loop_s uv_loop_t;

// The types alias those of Node-API so that the two APIs can be mixed without
// casts.
typedef struct napi_env__ js_env_t;
typedef struct napi_handle_scope__ js_handle_scope_t;
typedef struct napi_escapable_handle_scope__ js_escapable_handle_scope_t;
typedef struct napi_value__ js_value_t;
typedef struct napi_ref__ js_ref_t;
typedef struct napi_deferred__ js_deferred_t;
typedef struct napi_callback_info__ js_callback_info_t;
typedef struct napi_threadsafe_function__ js_threadsafe_function_t;
typedef struct napi_async_cleanup_hook_handle__ js_deferred_teardown_t;

typedef struct js_typed_callback_info_s js_typed_callback_info_t;
typedef struct js_string_view_s js_string_view_t;

typedef struct js_type_tag_s js_type_tag_t;
typedef struct js_property_descriptor_s js_property_descriptor_t;
typedef struct js_callback_signature_s js_callback_signature_t;

typedef js_value_t *(*js_function_cb)(js_env_t *, js_callback_info_t *);
typedef void (*js_finalize_cb)(js_env_t *, void *data, void *finalize_hint);
typedef void (*js_threadsafe_function_cb)(js_env_t *, js_value_t *function, void *context, void *data);
typedef void (*js_teardown_cb)(void *data);
typedef void (*js_deferred_teardown_cb)(js_deferred_teardown_t *, void *data);

enum {
  /**
   * There's a pending exception that, unless handled, will be propagated up the
   * JavaScript execution stack.
   */
  js_pending_exception = -1,

  /**
   * There was an uncaught exception that could not be propagated as the JavaScript
   * execution stack is empty.
   */
  js_uncaught_exception = -2,

  /**
   * The threadsafe function has been released, whether by every thread holding
   * it, in abort mode, or along with its environment.
   */
  js_closing = -3,

  /**
   * The queue of the threadsafe function is full.
   */
  js_queue_full = -4,

  /**
   * The engine does not support the operation.
   */
  js_unsupported = -5,

  /**
   * The operation is not valid in the current state, such as releasing a
   * threadsafe function that no thread holds.
   */
  js_invalid_state = -6,

  /**
   * The memory needed for the operation could not be allocated.
   */
  js_out_of_memory = -7,
};

typedef enum {
  js_undefined = 0,
  js_null = 1,
  js_boolean = 2,
  js_number = 3,
  js_string = 4,
  js_symbol = 5,
  js_object = 6,
  js_function = 7,
  js_external = 8,
  js_bigint = 9,
} js_value_type_t;

typedef enum {
  js_int8array = 0,
  js_uint8array = 1,
  js_uint8clampedarray = 2,
  js_int16array = 3,
  js_uint16array = 4,
  js_int32array = 5,
  js_uint32array = 6,
  js_float16array = 11,
  js_float32array = 7,
  js_float64array = 8,
  js_bigint64array = 9,
  js_biguint64array = 10,
} js_typedarray_type_t;

enum {
  // Numeric types

  js_int8 = 1 << 8 | js_number,
  js_uint8 = 2 << 8 | js_number,
  js_int16 = 3 << 8 | js_number,
  js_uint16 = 4 << 8 | js_number,
  js_int32 = 5 << 8 | js_number,
  js_uint32 = 6 << 8 | js_number,
  js_int64 = 7 << 8 | js_number,
  js_uint64 = 8 << 8 | js_number,
  js_float16 = 13 << 8 | js_number,
  js_float32 = 9 << 8 | js_number,
  js_float64 = 10 << 8 | js_number,
  js_bigint64 = 11 << 8 | js_number,
  js_biguint64 = 12 << 8 | js_number,
};

enum {
  js_writable = 1,
  js_enumerable = 1 << 1,
  js_configurable = 1 << 2,
  js_static = 1 << 10,
};

typedef enum {
  js_utf8 = 1,
  js_utf16le = 2,
  js_latin1 = 3,
} js_string_encoding_t;

typedef enum {
  js_threadsafe_function_release = 0,
  js_threadsafe_function_abort = 1
} js_threadsafe_function_release_mode_t;

typedef enum {
  js_threadsafe_function_nonblocking = 0,
  js_threadsafe_function_blocking = 1
} js_threadsafe_function_call_mode_t;

/** @version 0 */
struct js_property_descriptor_s {
  int version;

  /** @since 0 */
  js_value_t *name;

  /** @since 0 */
  void *data;

  /** @since 0 */
  int attributes;

  // One of:

  // Method

  /** @since 0 */
  js_function_cb method;

  // Accessor

  /** @since 0 */
  js_function_cb getter;

  /** @since 0 */
  js_function_cb setter;

  // Value

  /** @since 0 */
  js_value_t *value;
};

/** @version 0 */
struct js_type_tag_s {
  /** @since 0 */
  uint64_t lower;

  /** @since 0 */
  uint64_t upper;
};

/** @version 0 */
struct js_callback_signature_s {
  int version;

  /** @since 0 */
  int result;

  /** @since 0 */
  size_t args_len;

  /** @since 0 */
  int *args;
};

int
js_get_env_loop(js_env_t *env, uv_loop_t **result);

int
js_open_handle_scope(js_env_t *env, js_handle_scope_t **result);

int
js_close_handle_scope(js_env_t *env, js_handle_scope_t *scope);

int
js_open_escapable_handle_scope(js_env_t *env, js_escapable_handle_scope_t **result);

int
js_close_escapable_handle_scope(js_env_t *env, js_escapable_handle_scope_t *scope);

int
js_escape_handle(js_env_t *env, js_escapable_handle_scope_t *scope, js_value_t *escapee, js_value_t **result);

int
js_run_script(js_env_t *env, const char *file, size_t len, int offset, js_value_t *source, js_value_t **result);

int
js_create_reference(js_env_t *env, js_value_t *value, uint32_t count, js_ref_t **result);

int
js_delete_reference(js_env_t *env, js_ref_t *reference);

int
js_reference_ref(js_env_t *env, js_ref_t *reference, uint32_t *result);

int
js_reference_unref(js_env_t *env, js_ref_t *reference, uint32_t *result);

int
js_get_reference_value(js_env_t *env, js_ref_t *reference, js_value_t **result);

int
js_define_class(js_env_t *env, const char *name, size_t len, js_function_cb constructor, void *data, js_property_descriptor_t const properties[], size_t properties_len, js_value_t **result);

int
js_define_properties(js_env_t *env, js_value_t *object, js_property_descriptor_t const properties[], size_t properties_len);

int
js_wrap(js_env_t *env, js_value_t *object, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_ref_t **result);

int
js_unwrap(js_env_t *env, js_value_t *object, void **result);

int
js_remove_wrap(js_env_t *env, js_value_t *object, void **result);

int
js_add_type_tag(js_env_t *env, js_value_t *object, const js_type_tag_t *tag);

int
js_check_type_tag(js_env_t *env, js_value_t *object, const js_type_tag_t *tag, bool *result);

int
js_add_finalizer(js_env_t *env, js_value_t *object, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_ref_t **result);

int
js_create_int32(js_env_t *env, int32_t value, js_value_t **result);

int
js_create_uint32(js_env_t *env, uint32_t value, js_value_t **result);

int
js_create_int64(js_env_t *env, int64_t value, js_value_t **result);

int
js_create_double(js_env_t *env, double value, js_value_t **result);

int
js_create_bigint_int64(js_env_t *env, int64_t value, js_value_t **result);

int
js_create_bigint_uint64(js_env_t *env, uint64_t value, js_value_t **result);

int
js_create_bigint_words(js_env_t *env, int sign, const uint64_t *words, size_t len, js_value_t **result);

int
js_create_string_utf8(js_env_t *env, const utf8_t *str, size_t len, js_value_t **result);

int
js_create_string_utf16le(js_env_t *env, const utf16_t *str, size_t len, js_value_t **result);

int
js_create_string_latin1(js_env_t *env, const latin1_t *str, size_t len, js_value_t **result);

int
js_create_external_string_utf8(js_env_t *env, utf8_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied);

int
js_create_external_string_utf16le(js_env_t *env, utf16_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied);

int
js_create_external_string_latin1(js_env_t *env, latin1_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied);

int
js_create_property_key_utf8(js_env_t *env, const utf8_t *str, size_t len, js_value_t **result);

int
js_create_property_key_utf16le(js_env_t *env, const utf16_t *str, size_t len, js_value_t **result);

int
js_create_property_key_latin1(js_env_t *env, const latin1_t *str, size_t len, js_value_t **result);

int
js_create_symbol(js_env_t *env, js_value_t *description, js_value_t **result);

int
js_symbol_for(js_env_t *env, const char *description, size_t len, js_value_t **result);

int
js_create_object(js_env_t *env, js_value_t **result);

int
js_create_function(js_env_t *env, const char *name, size_t len, js_function_cb cb, void *data, js_value_t **result);

int
js_create_typed_function(js_env_t *env, const char *name, size_t len, js_function_cb cb, const js_callback_signature_t *signature, const void *address, void *data, js_value_t **result);

int
js_create_array(js_env_t *env, js_value_t **result);

int
js_create_array_with_length(js_env_t *env, size_t len, js_value_t **result);

int
js_create_external(js_env_t *env, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result);

int
js_create_date(js_env_t *env, double time, js_value_t **result);

int
js_create_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result);

int
js_create_type_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result);

int
js_create_range_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result);

int
js_create_syntax_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result);

int
js_create_promise(js_env_t *env, js_deferred_t **deferred, js_value_t **promise);

int
js_resolve_deferred(js_env_t *env, js_deferred_t *deferred, js_value_t *resolution);

int
js_reject_deferred(js_env_t *env, js_deferred_t *deferred, js_value_t *resolution);

int
js_create_arraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result);

int
js_create_external_arraybuffer(js_env_t *env, void *data, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result);

int
js_detach_arraybuffer(js_env_t *env, js_value_t *arraybuffer);

int
js_create_sharedarraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result);

int
js_create_unsafe_sharedarraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result);

int
js_create_typedarray(js_env_t *env, js_typedarray_type_t type, size_t len, js_value_t *arraybuffer, size_t offset, js_value_t **result);

int
js_create_dataview(js_env_t *env, size_t len, js_value_t *arraybuffer, size_t offset, js_value_t **result);

int
js_coerce_to_boolean(js_env_t *env, js_value_t *value, js_value_t **result);

int
js_coerce_to_number(js_env_t *env, js_value_t *value, js_value_t **result);

int
js_coerce_to_string(js_env_t *env, js_value_t *value, js_value_t **result);

int
js_coerce_to_object(js_env_t *env, js_value_t *value, js_value_t **result);

int
js_typeof(js_env_t *env, js_value_t *value, js_value_type_t *result);

int
js_instanceof(js_env_t *env, js_value_t *object, js_value_t *constructor, bool *result);

int
js_is_undefined(js_env_t *env, js_value_t *value, bool *result);

int
js_is_null(js_env_t *env, js_value_t *value, bool *result);

int
js_is_boolean(js_env_t *env, js_value_t *value, bool *result);

int
js_is_number(js_env_t *env, js_value_t *value, bool *result);

int
js_is_int32(js_env_t *env, js_value_t *value, bool *result);

int
js_is_uint32(js_env_t *env, js_value_t *value, bool *result);

int
js_is_string(js_env_t *env, js_value_t *value, bool *result);

int
js_is_symbol(js_env_t *env, js_value_t *value, bool *result);

int
js_is_object(js_env_t *env, js_value_t *value, bool *result);

int
js_is_function(js_env_t *env, js_value_t *value, bool *result);

int
js_is_array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_external(js_env_t *env, js_value_t *value, bool *result);

int
js_is_bigint(js_env_t *env, js_value_t *value, bool *result);

int
js_is_date(js_env_t *env, js_value_t *value, bool *result);

int
js_is_error(js_env_t *env, js_value_t *value, bool *result);

int
js_is_promise(js_env_t *env, js_value_t *value, bool *result);

int
js_is_arraybuffer(js_env_t *env, js_value_t *value, bool *result);

int
js_is_detached_arraybuffer(js_env_t *env, js_value_t *value, bool *result);

int
js_is_sharedarraybuffer(js_env_t *env, js_value_t *value, bool *result);

int
js_is_typedarray(js_env_t *env, js_value_t *value, bool *result);

int
js_is_int8array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_uint8array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_uint8clampedarray(js_env_t *env, js_value_t *value, bool *result);

int
js_is_int16array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_uint16array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_int32array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_uint32array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_float32array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_float64array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_bigint64array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_biguint64array(js_env_t *env, js_value_t *value, bool *result);

int
js_is_dataview(js_env_t *env, js_value_t *value, bool *result);

int
js_strict_equals(js_env_t *env, js_value_t *a, js_value_t *b, bool *result);

int
js_get_global(js_env_t *env, js_value_t **result);

int
js_get_undefined(js_env_t *env, js_value_t **result);

int
js_get_null(js_env_t *env, js_value_t **result);

int
js_get_boolean(js_env_t *env, bool value, js_value_t **result);

int
js_get_value_bool(js_env_t *env, js_value_t *value, bool *result);

int
js_get_value_int32(js_env_t *env, js_value_t *value, int32_t *result);

int
js_get_value_uint32(js_env_t *env, js_value_t *value, uint32_t *result);

int
js_get_value_int64(js_env_t *env, js_value_t *value, int64_t *result);

int
js_get_value_double(js_env_t *env, js_value_t *value, double *result);

int
js_get_value_bigint_int64(js_env_t *env, js_value_t *value, int64_t *result, bool *lossless);

int
js_get_value_bigint_uint64(js_env_t *env, js_value_t *value, uint64_t *result, bool *lossless);

int
js_get_value_bigint_words(js_env_t *env, js_value_t *value, int *sign, uint64_t *words, size_t len, size_t *result);

int
js_get_value_string_utf8(js_env_t *env, js_value_t *value, utf8_t *str, size_t len, size_t *result);

int
js_get_value_string_utf16le(js_env_t *env, js_value_t *value, utf16_t *str, size_t len, size_t *result);

int
js_get_value_string_latin1(js_env_t *env, js_value_t *value, latin1_t *str, size_t len, size_t *result);

int
js_get_value_external(js_env_t *env, js_value_t *value, void **result);

int
js_get_value_date(js_env_t *env, js_value_t *value, double *result);

int
js_get_array_length(js_env_t *env, js_value_t *value, uint32_t *result);

int
js_get_array_elements(js_env_t *env, js_value_t *array, js_value_t **elements, size_t len, size_t offset, uint32_t *result);

int
js_set_array_elements(js_env_t *env, js_value_t *array, js_value_t *const elements[], size_t len, size_t offset);

int
js_get_prototype(js_env_t *env, js_value_t *object, js_value_t **result);

int
js_get_property_names(js_env_t *env, js_value_t *object, js_value_t **result);

int
js_get_property(js_env_t *env, js_value_t *object, js_value_t *key, js_value_t **result);

int
js_has_property(js_env_t *env, js_value_t *object, js_value_t *key, bool *result);

int
js_set_property(js_env_t *env, js_value_t *object, js_value_t *key, js_value_t *value);

int
js_delete_property(js_env_t *env, js_value_t *object, js_value_t *key, bool *result);

int
js_get_named_property(js_env_t *env, js_value_t *object, const char *name, js_value_t **result);

int
js_has_named_property(js_env_t *env, js_value_t *object, const char *name, bool *result);

int
js_set_named_property(js_env_t *env, js_value_t *object, const char *name, js_value_t *value);

int
js_delete_named_property(js_env_t *env, js_value_t *object, const char *name, bool *result);

int
js_get_element(js_env_t *env, js_value_t *object, uint32_t index, js_value_t **result);

int
js_has_element(js_env_t *env, js_value_t *object, uint32_t index, bool *result);

int
js_set_element(js_env_t *env, js_value_t *object, uint32_t index, js_value_t *value);

int
js_delete_element(js_env_t *env, js_value_t *object, uint32_t index, bool *result);

int
js_get_callback_info(js_env_t *env, const js_callback_info_t *info, size_t *argc, js_value_t *argv[], js_value_t **receiver, void **data);

int
js_get_typed_callback_info(const js_typed_callback_info_t *info, js_env_t **env, void **data);

int
js_get_new_target(js_env_t *env, const js_callback_info_t *info, js_value_t **result);

int
js_get_arraybuffer_info(js_env_t *env, js_value_t *arraybuffer, void **data, size_t *len);

int
js_get_sharedarraybuffer_info(js_env_t *env, js_value_t *sharedarraybuffer, void **data, size_t *len);

int
js_get_typedarray_info(js_env_t *env, js_value_t *typedarray, js_typedarray_type_t *type, void **data, size_t *len, js_value_t **arraybuffer, size_t *offset);

int
js_get_dataview_info(js_env_t *env, js_value_t *dataview, void **data, size_t *len, js_value_t **arraybuffer, size_t *offset);

int
js_get_string_view(js_env_t *env, js_value_t *string, js_string_encoding_t *encoding, const void **str, size_t *len, js_string_view_t **result);

int
js_release_string_view(js_env_t *env, js_string_view_t *view);

int
js_call_function(js_env_t *env, js_value_t *receiver, js_value_t *function, size_t argc, js_value_t *const argv[], js_value_t **result);

int
js_call_function_with_checkpoint(js_env_t *env, js_value_t *receiver, js_value_t *function, size_t argc, js_value_t *const argv[], js_value_t **result);

int
js_new_instance(js_env_t *env, js_value_t *constructor, size_t argc, js_value_t *const argv[], js_value_t **result);

int
js_create_threadsafe_function(js_env_t *env, js_value_t *function, size_t queue_limit, size_t initial_thread_count, js_finalize_cb finalize_cb, void *finalize_hint, void *context, js_threadsafe_function_cb cb, js_threadsafe_function_t **result);

int
js_get_threadsafe_function_context(js_threadsafe_function_t *function, void **result);

int
js_call_threadsafe_function(js_threadsafe_function_t *function, void *data, js_threadsafe_function_call_mode_t mode);

int
js_acquire_threadsafe_function(js_threadsafe_function_t *function);

int
js_release_threadsafe_function(js_threadsafe_function_t *function, js_threadsafe_function_release_mode_t mode);

int
js_ref_threadsafe_function(js_env_t *env, js_threadsafe_function_t *function);

int
js_unref_threadsafe_function(js_env_t *env, js_threadsafe_function_t *function);

int
js_add_teardown_callback(js_env_t *env, js_teardown_cb callback, void *data);

int
js_remove_teardown_callback(js_env_t *env, js_teardown_cb callback, void *data);

int
js_add_deferred_teardown_callback(js_env_t *env, js_deferred_teardown_cb callback, void *data, js_deferred_teardown_t **result);

int
js_finish_deferred_teardown_callback(js_deferred_teardown_t *handle);

int
js_throw(js_env_t *env, js_value_t *error);

int
js_throw_error(js_env_t *env, const char *code, const char *message);

int
js_throw_verrorf(js_env_t *env, const char *code, const char *message, va_list args);

int
js_throw_errorf(js_env_t *env, const char *code, const char *message, ...);

int
js_throw_type_error(js_env_t *env, const char *code, const char *message);

int
js_throw_type_verrorf(js_env_t *env, const char *code, const char *message, va_list args);

int
js_throw_type_errorf(js_env_t *env, const char *code, const char *message, ...);

int
js_throw_range_error(js_env_t *env, const char *code, const char *message);

int
js_throw_range_verrorf(js_env_t *env, const char *code, const char *message, va_list args);

int
js_throw_range_errorf(js_env_t *env, const char *code, const char *message, ...);

int
js_throw_syntax_error(js_env_t *env, const char *code, const char *message);

int
js_throw_syntax_verrorf(js_env_t *env, const char *code, const char *message, va_list args);

int
js_throw_syntax_errorf(js_env_t *env, const char *code, const char *message, ...);

int
js_is_exception_pending(js_env_t *env, bool *result);

int
js_get_and_clear_last_exception(js_env_t *env, js_value_t **result);

int
js_fatal_exception(js_env_t *env, js_value_t *error);

int
js_adjust_external_memory(js_env_t *env, int64_t change_in_bytes, int64_t *result);

#ifdef __cplusplus
}
#endif

#endif // JS_H
