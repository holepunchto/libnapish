#include <assert.h>
#include <js.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "napi.h"

int
js_get_env_loop(js_env_t *env, uv_loop_t **result) {
  napi_status status = napi_get_uv_event_loop(env, result);
  return js_convert_from_status(status);
}

int
js_open_handle_scope(js_env_t *env, js_handle_scope_t **result) {
  napi_status status = napi_open_handle_scope(env, result);
  return js_convert_from_status(status);
}

int
js_close_handle_scope(js_env_t *env, js_handle_scope_t *scope) {
  napi_status status = napi_close_handle_scope(env, scope);
  return js_convert_from_status(status);
}

int
js_open_escapable_handle_scope(js_env_t *env, js_escapable_handle_scope_t **result) {
  napi_status status = napi_open_escapable_handle_scope(env, result);
  return js_convert_from_status(status);
}

int
js_close_escapable_handle_scope(js_env_t *env, js_escapable_handle_scope_t *scope) {
  napi_status status = napi_close_escapable_handle_scope(env, scope);
  return js_convert_from_status(status);
}

int
js_escape_handle(js_env_t *env, js_escapable_handle_scope_t *scope, js_value_t *escapee, js_value_t **result) {
  napi_status status = napi_escape_handle(env, scope, escapee, result);
  return js_convert_from_status(status);
}

int
js_run_script(js_env_t *env, const char *file, size_t len, int offset, js_value_t *source, js_value_t **result) {
  napi_status status = napi_run_script(env, source, result);
  return js_convert_from_status(status);
}

int
js_create_reference(js_env_t *env, js_value_t *value, uint32_t count, js_ref_t **result) {
  napi_status status = napi_create_reference(env, value, count, result);
  return js_convert_from_status(status);
}

int
js_delete_reference(js_env_t *env, js_ref_t *reference) {
  napi_status status = napi_delete_reference(env, reference);
  return js_convert_from_status(status);
}

int
js_reference_ref(js_env_t *env, js_ref_t *reference, uint32_t *result) {
  napi_status status = napi_reference_ref(env, reference, result);
  return js_convert_from_status(status);
}

int
js_reference_unref(js_env_t *env, js_ref_t *reference, uint32_t *result) {
  napi_status status = napi_reference_unref(env, reference, result);
  return js_convert_from_status(status);
}

int
js_get_reference_value(js_env_t *env, js_ref_t *reference, js_value_t **result) {
  napi_status status = napi_get_reference_value(env, reference, result);
  return js_convert_from_status(status);
}

int
js_define_class(js_env_t *env, const char *name, size_t len, js_function_cb constructor, void *data, js_property_descriptor_t const properties[], size_t properties_len, js_value_t **result) {
  napi_property_descriptor *napi_properties = js_convert_to_property_descriptors(properties, properties_len);

  if (napi_properties == NULL && properties_len != 0) return js_out_of_memory;

  napi_status status = napi_define_class(env, name, len, constructor, data, properties_len, napi_properties, result);

  free(napi_properties);

  return js_convert_from_status(status);
}

int
js_define_properties(js_env_t *env, js_value_t *object, js_property_descriptor_t const properties[], size_t properties_len) {
  napi_property_descriptor *napi_properties = js_convert_to_property_descriptors(properties, properties_len);

  if (napi_properties == NULL && properties_len != 0) return js_out_of_memory;

  napi_status status = napi_define_properties(env, object, properties_len, napi_properties);

  free(napi_properties);

  return js_convert_from_status(status);
}

int
js_wrap(js_env_t *env, js_value_t *object, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_ref_t **result) {
  napi_status status = napi_wrap(env, object, data, finalize_cb, finalize_hint, result);
  return js_convert_from_status(status);
}

int
js_unwrap(js_env_t *env, js_value_t *object, void **result) {
  napi_status status = napi_unwrap(env, object, result);
  return js_convert_from_status(status);
}

int
js_remove_wrap(js_env_t *env, js_value_t *object, void **result) {
  napi_status status = napi_remove_wrap(env, object, result);
  return js_convert_from_status(status);
}

int
js_add_type_tag(js_env_t *env, js_value_t *object, const js_type_tag_t *tag) {
  napi_type_tag napi_tag = {tag->lower, tag->upper};
  napi_status status = napi_type_tag_object(env, object, &napi_tag);
  return js_convert_from_status(status);
}

int
js_check_type_tag(js_env_t *env, js_value_t *object, const js_type_tag_t *tag, bool *result) {
  napi_type_tag napi_tag = {tag->lower, tag->upper};
  napi_status status = napi_check_object_type_tag(env, object, &napi_tag, result);
  return js_convert_from_status(status);
}

int
js_add_finalizer(js_env_t *env, js_value_t *object, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_ref_t **result) {
  napi_status status = napi_add_finalizer(env, object, data, finalize_cb, finalize_hint, result);
  return js_convert_from_status(status);
}

int
js_create_int32(js_env_t *env, int32_t value, js_value_t **result) {
  napi_status status = napi_create_int32(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_uint32(js_env_t *env, uint32_t value, js_value_t **result) {
  napi_status status = napi_create_uint32(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_int64(js_env_t *env, int64_t value, js_value_t **result) {
  napi_status status = napi_create_int64(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_double(js_env_t *env, double value, js_value_t **result) {
  napi_status status = napi_create_double(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_bigint_int64(js_env_t *env, int64_t value, js_value_t **result) {
  napi_status status = napi_create_bigint_int64(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_bigint_uint64(js_env_t *env, uint64_t value, js_value_t **result) {
  napi_status status = napi_create_bigint_uint64(env, value, result);
  return js_convert_from_status(status);
}

int
js_create_bigint_words(js_env_t *env, int sign, const uint64_t *words, size_t len, js_value_t **result) {
  napi_status status = napi_create_bigint_words(env, sign, len, words, result);
  return js_convert_from_status(status);
}

int
js_create_string_utf8(js_env_t *env, const utf8_t *str, size_t len, js_value_t **result) {
  napi_status status = napi_create_string_utf8(env, (const char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_create_string_utf16le(js_env_t *env, const utf16_t *str, size_t len, js_value_t **result) {
  napi_status status = napi_create_string_utf16(env, str, len, result);
  return js_convert_from_status(status);
}

int
js_create_string_latin1(js_env_t *env, const latin1_t *str, size_t len, js_value_t **result) {
  napi_status status = napi_create_string_latin1(env, (const char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_create_external_string_utf8(js_env_t *env, utf8_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied) {
  if (copied) *copied = true;

  napi_status status = napi_create_string_utf8(env, (const char *) str, len, result);

  if (status == napi_ok && finalize_cb) finalize_cb(env, str, finalize_hint);

  return js_convert_from_status(status);
}

int
js_create_external_string_utf16le(js_env_t *env, utf16_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied) {
  napi_status status = node_api_create_external_string_utf16(env, str, len, finalize_cb, finalize_hint, result, copied);
  return js_convert_from_status(status);
}

int
js_create_external_string_latin1(js_env_t *env, latin1_t *str, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result, bool *copied) {
  napi_status status = node_api_create_external_string_latin1(env, (char *) str, len, finalize_cb, finalize_hint, result, copied);
  return js_convert_from_status(status);
}

int
js_create_property_key_utf8(js_env_t *env, const utf8_t *str, size_t len, js_value_t **result) {
  napi_status status = node_api_create_property_key_utf8(env, (const char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_create_property_key_utf16le(js_env_t *env, const utf16_t *str, size_t len, js_value_t **result) {
  napi_status status = node_api_create_property_key_utf16(env, str, len, result);
  return js_convert_from_status(status);
}

int
js_create_property_key_latin1(js_env_t *env, const latin1_t *str, size_t len, js_value_t **result) {
  napi_status status = node_api_create_property_key_latin1(env, (const char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_create_symbol(js_env_t *env, js_value_t *description, js_value_t **result) {
  napi_status status = napi_create_symbol(env, description, result);
  return js_convert_from_status(status);
}

int
js_symbol_for(js_env_t *env, const char *description, size_t len, js_value_t **result) {
  napi_status status = node_api_symbol_for(env, description, len, result);
  return js_convert_from_status(status);
}

int
js_create_object(js_env_t *env, js_value_t **result) {
  napi_status status = napi_create_object(env, result);
  return js_convert_from_status(status);
}

int
js_create_function(js_env_t *env, const char *name, size_t len, js_function_cb cb, void *data, js_value_t **result) {
  napi_status status = napi_create_function(env, name, len, cb, data, result);
  return js_convert_from_status(status);
}

int
js_create_typed_function(js_env_t *env, const char *name, size_t len, js_function_cb cb, const js_callback_signature_t *signature, const void *address, void *data, js_value_t **result) {
  return js_create_function(env, name, len, cb, data, result);
}

int
js_create_array(js_env_t *env, js_value_t **result) {
  napi_status status = napi_create_array(env, result);
  return js_convert_from_status(status);
}

int
js_create_array_with_length(js_env_t *env, size_t len, js_value_t **result) {
  napi_status status = napi_create_array_with_length(env, len, result);
  return js_convert_from_status(status);
}

int
js_create_external(js_env_t *env, void *data, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result) {
  napi_status status = napi_create_external(env, data, finalize_cb, finalize_hint, result);
  return js_convert_from_status(status);
}

int
js_create_date(js_env_t *env, double time, js_value_t **result) {
  napi_status status = napi_create_date(env, time, result);
  return js_convert_from_status(status);
}

int
js_create_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result) {
  napi_status status = napi_create_error(env, code, message, result);
  return js_convert_from_status(status);
}

int
js_create_type_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result) {
  napi_status status = napi_create_type_error(env, code, message, result);
  return js_convert_from_status(status);
}

int
js_create_range_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result) {
  napi_status status = napi_create_range_error(env, code, message, result);
  return js_convert_from_status(status);
}

int
js_create_syntax_error(js_env_t *env, js_value_t *code, js_value_t *message, js_value_t **result) {
  napi_status status = node_api_create_syntax_error(env, code, message, result);
  return js_convert_from_status(status);
}

int
js_create_promise(js_env_t *env, js_deferred_t **deferred, js_value_t **promise) {
  napi_status status = napi_create_promise(env, deferred, promise);
  return js_convert_from_status(status);
}

int
js_resolve_deferred(js_env_t *env, js_deferred_t *deferred, js_value_t *resolution) {
  napi_status status = napi_resolve_deferred(env, deferred, resolution);
  return js_convert_from_status(status);
}

int
js_reject_deferred(js_env_t *env, js_deferred_t *deferred, js_value_t *resolution) {
  napi_status status = napi_reject_deferred(env, deferred, resolution);
  return js_convert_from_status(status);
}

int
js_create_arraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result) {
  napi_status status = napi_create_arraybuffer(env, len, data, result);
  return js_convert_from_status(status);
}

int
js_create_external_arraybuffer(js_env_t *env, void *data, size_t len, js_finalize_cb finalize_cb, void *finalize_hint, js_value_t **result) {
  napi_status status = napi_create_external_arraybuffer(env, data, len, finalize_cb, finalize_hint, result);
  return js_convert_from_status(status);
}

int
js_detach_arraybuffer(js_env_t *env, js_value_t *arraybuffer) {
  napi_status status = napi_detach_arraybuffer(env, arraybuffer);
  return js_convert_from_status(status);
}

int
js_create_typedarray(js_env_t *env, js_typedarray_type_t type, size_t len, js_value_t *arraybuffer, size_t offset, js_value_t **result) {
  napi_status status = napi_create_typedarray(env, js_convert_to_typedarray_type(type), len, arraybuffer, offset, result);
  return js_convert_from_status(status);
}

int
js_create_dataview(js_env_t *env, size_t len, js_value_t *arraybuffer, size_t offset, js_value_t **result) {
  napi_status status = napi_create_dataview(env, len, arraybuffer, offset, result);
  return js_convert_from_status(status);
}

int
js_coerce_to_boolean(js_env_t *env, js_value_t *value, js_value_t **result) {
  napi_status status = napi_coerce_to_bool(env, value, result);
  return js_convert_from_status(status);
}

int
js_coerce_to_number(js_env_t *env, js_value_t *value, js_value_t **result) {
  napi_status status = napi_coerce_to_number(env, value, result);
  return js_convert_from_status(status);
}

int
js_coerce_to_string(js_env_t *env, js_value_t *value, js_value_t **result) {
  napi_status status = napi_coerce_to_string(env, value, result);
  return js_convert_from_status(status);
}

int
js_coerce_to_object(js_env_t *env, js_value_t *value, js_value_t **result) {
  napi_status status = napi_coerce_to_object(env, value, result);
  return js_convert_from_status(status);
}

int
js_typeof(js_env_t *env, js_value_t *value, js_value_type_t *result) {
  napi_valuetype napi_type;

  napi_status status = napi_typeof(env, value, &napi_type);

  if (status == napi_ok) *result = js_convert_from_valuetype(napi_type);

  return js_convert_from_status(status);
}

int
js_instanceof(js_env_t *env, js_value_t *object, js_value_t *constructor, bool *result) {
  napi_status status = napi_instanceof(env, object, constructor, result);
  return js_convert_from_status(status);
}

static int
js__is_type(js_env_t *env, js_value_t *value, napi_valuetype type, bool *result) {
  napi_valuetype actual;

  napi_status status = napi_typeof(env, value, &actual);

  if (status == napi_ok) *result = actual == type;

  return js_convert_from_status(status);
}

static int
js__is_integer_in_range(js_env_t *env, js_value_t *value, double min, double max, bool *result) {
  int err = js__is_type(env, value, napi_number, result);

  if (err < 0 || !*result) return err;

  double number;
  err = js_get_value_double(env, value, &number);

  if (err < 0) return err;

  double integral;

  *result = modf(number, &integral) == 0.0 && integral >= min && integral <= max;

  return 0;
}

static int
js__is_typedarray_type(js_env_t *env, js_value_t *value, napi_typedarray_type type, bool *result) {
  napi_status status = napi_is_typedarray(env, value, result);

  if (status != napi_ok || !*result) return js_convert_from_status(status);

  napi_typedarray_type actual;
  status = napi_get_typedarray_info(env, value, &actual, NULL, NULL, NULL, NULL);

  if (status == napi_ok) *result = actual == type;

  return js_convert_from_status(status);
}

int
js_is_undefined(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_undefined, result);
}

int
js_is_null(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_null, result);
}

int
js_is_boolean(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_boolean, result);
}

int
js_is_number(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_number, result);
}

int
js_is_int32(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_integer_in_range(env, value, INT32_MIN, INT32_MAX, result);
}

int
js_is_uint32(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_integer_in_range(env, value, 0, UINT32_MAX, result);
}

int
js_is_string(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_string, result);
}

int
js_is_symbol(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_symbol, result);
}

int
js_is_object(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_object, result);
}

int
js_is_function(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_function, result);
}

int
js_is_array(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_array(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_external(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_external, result);
}

int
js_is_bigint(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_type(env, value, napi_bigint, result);
}

int
js_is_date(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_date(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_error(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_error(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_promise(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_promise(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_arraybuffer(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_arraybuffer(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_detached_arraybuffer(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_detached_arraybuffer(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_typedarray(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_typedarray(env, value, result);
  return js_convert_from_status(status);
}

int
js_is_int8array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_int8_array, result);
}

int
js_is_uint8array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_uint8_array, result);
}

int
js_is_uint8clampedarray(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_uint8_clamped_array, result);
}

int
js_is_int16array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_int16_array, result);
}

int
js_is_uint16array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_uint16_array, result);
}

int
js_is_int32array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_int32_array, result);
}

int
js_is_uint32array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_uint32_array, result);
}

int
js_is_float32array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_float32_array, result);
}

int
js_is_float64array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_float64_array, result);
}

int
js_is_bigint64array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_bigint64_array, result);
}

int
js_is_biguint64array(js_env_t *env, js_value_t *value, bool *result) {
  return js__is_typedarray_type(env, value, napi_biguint64_array, result);
}

int
js_is_dataview(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_is_dataview(env, value, result);
  return js_convert_from_status(status);
}

int
js_strict_equals(js_env_t *env, js_value_t *a, js_value_t *b, bool *result) {
  napi_status status = napi_strict_equals(env, a, b, result);
  return js_convert_from_status(status);
}

int
js_get_global(js_env_t *env, js_value_t **result) {
  napi_status status = napi_get_global(env, result);
  return js_convert_from_status(status);
}

int
js_get_undefined(js_env_t *env, js_value_t **result) {
  napi_status status = napi_get_undefined(env, result);
  return js_convert_from_status(status);
}

int
js_get_null(js_env_t *env, js_value_t **result) {
  napi_status status = napi_get_null(env, result);
  return js_convert_from_status(status);
}

int
js_get_boolean(js_env_t *env, bool value, js_value_t **result) {
  napi_status status = napi_get_boolean(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_bool(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = napi_get_value_bool(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_int32(js_env_t *env, js_value_t *value, int32_t *result) {
  napi_status status = napi_get_value_int32(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_uint32(js_env_t *env, js_value_t *value, uint32_t *result) {
  napi_status status = napi_get_value_uint32(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_int64(js_env_t *env, js_value_t *value, int64_t *result) {
  napi_status status = napi_get_value_int64(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_double(js_env_t *env, js_value_t *value, double *result) {
  napi_status status = napi_get_value_double(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_bigint_int64(js_env_t *env, js_value_t *value, int64_t *result, bool *lossless) {
  napi_status status = napi_get_value_bigint_int64(env, value, result, lossless);
  return js_convert_from_status(status);
}

int
js_get_value_bigint_uint64(js_env_t *env, js_value_t *value, uint64_t *result, bool *lossless) {
  napi_status status = napi_get_value_bigint_uint64(env, value, result, lossless);
  return js_convert_from_status(status);
}

int
js_get_value_bigint_words(js_env_t *env, js_value_t *value, int *sign, uint64_t *words, size_t len, size_t *result) {
  size_t count = len;

  napi_status status = napi_get_value_bigint_words(env, value, sign, &count, words);

  if (result) *result = count;

  return js_convert_from_status(status);
}

int
js_get_value_string_utf8(js_env_t *env, js_value_t *value, utf8_t *str, size_t len, size_t *result) {
  napi_status status = napi_get_value_string_utf8(env, value, (char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_get_value_string_utf16le(js_env_t *env, js_value_t *value, utf16_t *str, size_t len, size_t *result) {
  napi_status status = napi_get_value_string_utf16(env, value, str, len, result);
  return js_convert_from_status(status);
}

int
js_get_value_string_latin1(js_env_t *env, js_value_t *value, latin1_t *str, size_t len, size_t *result) {
  napi_status status = napi_get_value_string_latin1(env, value, (char *) str, len, result);
  return js_convert_from_status(status);
}

int
js_get_value_external(js_env_t *env, js_value_t *value, void **result) {
  napi_status status = napi_get_value_external(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_value_date(js_env_t *env, js_value_t *value, double *result) {
  napi_status status = napi_get_date_value(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_array_length(js_env_t *env, js_value_t *value, uint32_t *result) {
  napi_status status = napi_get_array_length(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_array_elements(js_env_t *env, js_value_t *array, js_value_t **elements, size_t len, size_t offset, uint32_t *result) {
  uint32_t array_len;

  napi_status status = napi_get_array_length(env, array, &array_len);

  if (status != napi_ok) return js_convert_from_status(status);

  uint32_t written = 0;

  for (size_t i = offset; written < len && i < array_len; i++, written++) {
    status = napi_get_element(env, array, (uint32_t) i, &elements[written]);

    if (status != napi_ok) return js_convert_from_status(status);
  }

  if (result) *result = written;

  return 0;
}

int
js_set_array_elements(js_env_t *env, js_value_t *array, js_value_t *const elements[], size_t len, size_t offset) {
  for (size_t i = 0; i < len; i++) {
    napi_status status = napi_set_element(env, array, (uint32_t) (offset + i), elements[i]);

    if (status != napi_ok) return js_convert_from_status(status);
  }

  return 0;
}

int
js_get_prototype(js_env_t *env, js_value_t *object, js_value_t **result) {
  napi_status status = napi_get_prototype(env, object, result);
  return js_convert_from_status(status);
}

int
js_get_property_names(js_env_t *env, js_value_t *object, js_value_t **result) {
  napi_status status = napi_get_property_names(env, object, result);
  return js_convert_from_status(status);
}

int
js_get_property(js_env_t *env, js_value_t *object, js_value_t *key, js_value_t **result) {
  napi_status status = napi_get_property(env, object, key, result);
  return js_convert_from_status(status);
}

int
js_has_property(js_env_t *env, js_value_t *object, js_value_t *key, bool *result) {
  napi_status status = napi_has_property(env, object, key, result);
  return js_convert_from_status(status);
}

int
js_set_property(js_env_t *env, js_value_t *object, js_value_t *key, js_value_t *value) {
  napi_status status = napi_set_property(env, object, key, value);
  return js_convert_from_status(status);
}

int
js_delete_property(js_env_t *env, js_value_t *object, js_value_t *key, bool *result) {
  napi_status status = napi_delete_property(env, object, key, result);
  return js_convert_from_status(status);
}

int
js_get_named_property(js_env_t *env, js_value_t *object, const char *name, js_value_t **result) {
  napi_status status = napi_get_named_property(env, object, name, result);
  return js_convert_from_status(status);
}

int
js_has_named_property(js_env_t *env, js_value_t *object, const char *name, bool *result) {
  napi_status status = napi_has_named_property(env, object, name, result);
  return js_convert_from_status(status);
}

int
js_set_named_property(js_env_t *env, js_value_t *object, const char *name, js_value_t *value) {
  napi_status status = napi_set_named_property(env, object, name, value);
  return js_convert_from_status(status);
}

int
js_delete_named_property(js_env_t *env, js_value_t *object, const char *name, bool *result) {
  napi_status status;

  napi_value key;
  status = napi_create_string_utf8(env, name, NAPI_AUTO_LENGTH, &key);

  if (status == napi_ok) status = napi_delete_property(env, object, key, result);

  return js_convert_from_status(status);
}

int
js_get_element(js_env_t *env, js_value_t *object, uint32_t index, js_value_t **result) {
  napi_status status = napi_get_element(env, object, index, result);
  return js_convert_from_status(status);
}

int
js_has_element(js_env_t *env, js_value_t *object, uint32_t index, bool *result) {
  napi_status status = napi_has_element(env, object, index, result);
  return js_convert_from_status(status);
}

int
js_set_element(js_env_t *env, js_value_t *object, uint32_t index, js_value_t *value) {
  napi_status status = napi_set_element(env, object, index, value);
  return js_convert_from_status(status);
}

int
js_delete_element(js_env_t *env, js_value_t *object, uint32_t index, bool *result) {
  napi_status status = napi_delete_element(env, object, index, result);
  return js_convert_from_status(status);
}

int
js_get_callback_info(js_env_t *env, const js_callback_info_t *info, size_t *argc, js_value_t *argv[], js_value_t **receiver, void **data) {
  napi_status status = napi_get_cb_info(env, (js_callback_info_t *) info, argc, argv, receiver, data);
  return js_convert_from_status(status);
}

int
js_get_typed_callback_info(const js_typed_callback_info_t *info, js_env_t **env, void **data) {
  return 0;
}

int
js_get_new_target(js_env_t *env, const js_callback_info_t *info, js_value_t **result) {
  napi_status status = napi_get_new_target(env, (js_callback_info_t *) info, result);
  return js_convert_from_status(status);
}

int
js_get_arraybuffer_info(js_env_t *env, js_value_t *arraybuffer, void **data, size_t *len) {
  napi_status status = napi_get_arraybuffer_info(env, arraybuffer, data, len);
  return js_convert_from_status(status);
}

int
js_get_typedarray_info(js_env_t *env, js_value_t *typedarray, js_typedarray_type_t *type, void **data, size_t *len, js_value_t **arraybuffer, size_t *offset) {
  napi_typedarray_type napi_type;

  napi_status status = napi_get_typedarray_info(env, typedarray, type == NULL ? NULL : &napi_type, len, data, arraybuffer, offset);

  if (status == napi_ok && type) *type = js_convert_from_typedarray_type(napi_type);

  return js_convert_from_status(status);
}

int
js_get_dataview_info(js_env_t *env, js_value_t *dataview, void **data, size_t *len, js_value_t **arraybuffer, size_t *offset) {
  napi_status status = napi_get_dataview_info(env, dataview, len, data, arraybuffer, offset);
  return js_convert_from_status(status);
}

int
js_get_string_view(js_env_t *env, js_value_t *string, js_string_encoding_t *encoding, const void **str, size_t *len, js_string_view_t **result) {
  size_t view_len;

  napi_status status = napi_get_value_string_utf8(env, string, NULL, 0, &view_len);

  if (status != napi_ok) return js_convert_from_status(status);

  char *view = malloc(view_len + 1 /* NULL */);

  if (view == NULL) return js_out_of_memory;

  status = napi_get_value_string_utf8(env, string, view, view_len + 1 /* NULL */, NULL);

  if (status != napi_ok) {
    free(view);

    return js_convert_from_status(status);
  }

  if (encoding) *encoding = js_utf8;

  if (str) *str = view;

  if (len) *len = view_len;

  *result = (js_string_view_t *) view;

  return 0;
}

int
js_release_string_view(js_env_t *env, js_string_view_t *view) {
  free(view);

  return 0;
}

int
js_call_function(js_env_t *env, js_value_t *receiver, js_value_t *function, size_t argc, js_value_t *const argv[], js_value_t **result) {
  napi_status status = napi_call_function(env, receiver, function, argc, argv, result);
  return js_convert_from_status(status);
}

int
js_call_function_with_checkpoint(js_env_t *env, js_value_t *receiver, js_value_t *function, size_t argc, js_value_t *const argv[], js_value_t **result) {
  napi_status status = napi_make_callback(env, NULL, receiver, function, argc, argv, result);

  if (status != napi_pending_exception) return js_convert_from_status(status);

  napi_value error;
  status = napi_get_and_clear_last_exception(env, &error);
  assert(status == napi_ok);

  status = napi_fatal_exception(env, error);
  assert(status == napi_ok);

  (void) status;

  return js_uncaught_exception;
}

int
js_new_instance(js_env_t *env, js_value_t *constructor, size_t argc, js_value_t *const argv[], js_value_t **result) {
  napi_status status = napi_new_instance(env, constructor, argc, argv, result);
  return js_convert_from_status(status);
}

typedef struct {
  js_threadsafe_function_cb cb;
  void *context;
  js_finalize_cb finalize_cb;
  void *finalize_hint;
} js_threadsafe_function_info_t;

static void
js__threadsafe_function_call(napi_env env, napi_value function, void *context, void *data) {
  js_threadsafe_function_info_t *info = context;

  info->cb(env, function, info->context, data);
}

static void
js__threadsafe_function_finalize(napi_env env, void *data, void *hint) {
  js_threadsafe_function_info_t *info = data;

  if (info->finalize_cb) info->finalize_cb(env, info->context, info->finalize_hint);

  free(info);
}

int
js_create_threadsafe_function(js_env_t *env, js_value_t *function, size_t queue_limit, size_t initial_thread_count, js_finalize_cb finalize_cb, void *finalize_hint, void *context, js_threadsafe_function_cb cb, js_threadsafe_function_t **result) {
  napi_value resource_name;

  napi_status status = napi_create_string_utf8(env, "js_threadsafe_function_t", NAPI_AUTO_LENGTH, &resource_name);

  if (status != napi_ok) return js_convert_from_status(status);

  js_threadsafe_function_info_t *info = malloc(sizeof(*info));

  if (info == NULL) return js_out_of_memory;

  *info = (js_threadsafe_function_info_t){cb, context, finalize_cb, finalize_hint};

  status = napi_create_threadsafe_function(env, function, NULL, resource_name, queue_limit, initial_thread_count, info, js__threadsafe_function_finalize, info, cb ? js__threadsafe_function_call : NULL, result);

  if (status != napi_ok) free(info);

  return js_convert_from_status(status);
}

int
js_get_threadsafe_function_context(js_threadsafe_function_t *function, void **result) {
  js_threadsafe_function_info_t *info;

  napi_status status = napi_get_threadsafe_function_context(function, (void **) &info);

  if (status == napi_ok) *result = info->context;

  return js_convert_from_status(status);
}

int
js_call_threadsafe_function(js_threadsafe_function_t *function, void *data, js_threadsafe_function_call_mode_t mode) {
  napi_status status = napi_call_threadsafe_function(function, data, js_convert_to_threadsafe_function_call_mode(mode));
  return js_convert_from_threadsafe_function_status(status);
}

int
js_acquire_threadsafe_function(js_threadsafe_function_t *function) {
  napi_status status = napi_acquire_threadsafe_function(function);
  return js_convert_from_threadsafe_function_status(status);
}

int
js_release_threadsafe_function(js_threadsafe_function_t *function, js_threadsafe_function_release_mode_t mode) {
  napi_status status = napi_release_threadsafe_function(function, js_convert_to_threadsafe_function_release_mode(mode));
  return js_convert_from_threadsafe_function_status(status);
}

int
js_ref_threadsafe_function(js_env_t *env, js_threadsafe_function_t *function) {
  napi_status status = napi_ref_threadsafe_function(env, function);
  return js_convert_from_status(status);
}

int
js_unref_threadsafe_function(js_env_t *env, js_threadsafe_function_t *function) {
  napi_status status = napi_unref_threadsafe_function(env, function);
  return js_convert_from_status(status);
}

int
js_add_teardown_callback(js_env_t *env, js_teardown_cb callback, void *data) {
  napi_status status = napi_add_env_cleanup_hook(env, callback, data);
  return js_convert_from_status(status);
}

int
js_remove_teardown_callback(js_env_t *env, js_teardown_cb callback, void *data) {
  napi_status status = napi_remove_env_cleanup_hook(env, callback, data);
  return js_convert_from_status(status);
}

int
js_add_deferred_teardown_callback(js_env_t *env, js_deferred_teardown_cb callback, void *data, js_deferred_teardown_t **result) {
  napi_status status = napi_add_async_cleanup_hook(env, callback, data, result);
  return js_convert_from_status(status);
}

int
js_finish_deferred_teardown_callback(js_deferred_teardown_t *handle) {
  napi_status status = napi_remove_async_cleanup_hook(handle);
  return js_convert_from_status(status);
}

int
js_throw(js_env_t *env, js_value_t *error) {
  napi_status status = napi_throw(env, error);
  return js_convert_from_status(status);
}

int
js_throw_error(js_env_t *env, const char *code, const char *message) {
  napi_status status = napi_throw_error(env, code, message);
  return js_convert_from_status(status);
}

static int
js__throw_verrorf(js_env_t *env, int (*throw_error)(js_env_t *, const char *, const char *), const char *code, const char *message, va_list args) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"

  va_list args_copy;
  va_copy(args_copy, args);

  int size = vsnprintf(NULL, 0, message, args_copy);

  va_end(args_copy);

  if (size < 0) return throw_error(env, code, message);

  char *formatted = malloc((size_t) size + 1 /* NULL */);

  if (formatted == NULL) return js_out_of_memory;

  va_copy(args_copy, args);

  vsnprintf(formatted, (size_t) size + 1 /* NULL */, message, args_copy);

  va_end(args_copy);

#pragma GCC diagnostic pop

  int err = throw_error(env, code, formatted);

  free(formatted);

  return err;
}

int
js_throw_verrorf(js_env_t *env, const char *code, const char *message, va_list args) {
  return js__throw_verrorf(env, js_throw_error, code, message, args);
}

int
js_throw_errorf(js_env_t *env, const char *code, const char *message, ...) {
  va_list args;
  va_start(args, message);

  int err = js_throw_verrorf(env, code, message, args);

  va_end(args);

  return err;
}

int
js_throw_type_error(js_env_t *env, const char *code, const char *message) {
  napi_status status = napi_throw_type_error(env, code, message);
  return js_convert_from_status(status);
}

int
js_throw_type_verrorf(js_env_t *env, const char *code, const char *message, va_list args) {
  return js__throw_verrorf(env, js_throw_type_error, code, message, args);
}

int
js_throw_type_errorf(js_env_t *env, const char *code, const char *message, ...) {
  va_list args;
  va_start(args, message);

  int err = js_throw_type_verrorf(env, code, message, args);

  va_end(args);

  return err;
}

int
js_throw_range_error(js_env_t *env, const char *code, const char *message) {
  napi_status status = napi_throw_range_error(env, code, message);
  return js_convert_from_status(status);
}

int
js_throw_range_verrorf(js_env_t *env, const char *code, const char *message, va_list args) {
  return js__throw_verrorf(env, js_throw_range_error, code, message, args);
}

int
js_throw_range_errorf(js_env_t *env, const char *code, const char *message, ...) {
  va_list args;
  va_start(args, message);

  int err = js_throw_range_verrorf(env, code, message, args);

  va_end(args);

  return err;
}

int
js_throw_syntax_error(js_env_t *env, const char *code, const char *message) {
  napi_status status = node_api_throw_syntax_error(env, code, message);
  return js_convert_from_status(status);
}

int
js_throw_syntax_verrorf(js_env_t *env, const char *code, const char *message, va_list args) {
  return js__throw_verrorf(env, js_throw_syntax_error, code, message, args);
}

int
js_throw_syntax_errorf(js_env_t *env, const char *code, const char *message, ...) {
  va_list args;
  va_start(args, message);

  int err = js_throw_syntax_verrorf(env, code, message, args);

  va_end(args);

  return err;
}

int
js_is_exception_pending(js_env_t *env, bool *result) {
  napi_status status = napi_is_exception_pending(env, result);
  return js_convert_from_status(status);
}

int
js_get_and_clear_last_exception(js_env_t *env, js_value_t **result) {
  napi_status status = napi_get_and_clear_last_exception(env, result);
  return js_convert_from_status(status);
}

int
js_fatal_exception(js_env_t *env, js_value_t *error) {
  napi_status status = napi_fatal_exception(env, error);
  return js_convert_from_status(status);
}

int
js_adjust_external_memory(js_env_t *env, int64_t change_in_bytes, int64_t *result) {
  napi_status status = napi_adjust_external_memory(env, change_in_bytes, result);
  return js_convert_from_status(status);
}
