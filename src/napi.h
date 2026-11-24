#ifndef NAPISH_NAPI_H
#define NAPISH_NAPI_H

#include <bare/module.h>
#include <stdlib.h>

#define NAPI_VERSION BARE_MODULE_NAPI_VERSION

#define NODE_API_EXPERIMENTAL_NOGC_ENV_OPT_OUT
#define NODE_API_EXPERIMENTAL_BASIC_ENV_OPT_OUT

#include <node_api.h>

static inline int
js_convert_from_status(napi_status status) {
  switch (status) {
  case napi_ok:
    return 0;
  default:
    return js_pending_exception;
  }
}

static inline js_value_type_t
js_convert_from_valuetype(napi_valuetype type) {
  switch (type) {
  case napi_undefined:
    return js_undefined;
  case napi_null:
  default:
    return js_null;
  case napi_boolean:
    return js_boolean;
  case napi_number:
    return js_number;
  case napi_string:
    return js_string;
  case napi_symbol:
    return js_symbol;
  case napi_object:
    return js_object;
  case napi_function:
    return js_function;
  case napi_external:
    return js_external;
  case napi_bigint:
    return js_bigint;
  }
}

static inline js_typedarray_type_t
js_convert_from_typedarray_type(napi_typedarray_type type) {
  switch (type) {
  case napi_int8_array:
    return js_int8array;
  case napi_uint8_array:
  default:
    return js_uint8array;
  case napi_uint8_clamped_array:
    return js_uint8clampedarray;
  case napi_int16_array:
    return js_int16array;
  case napi_uint16_array:
    return js_uint16array;
  case napi_int32_array:
    return js_int32array;
  case napi_uint32_array:
    return js_uint32array;
  case napi_float32_array:
    return js_float32array;
  case napi_float64_array:
    return js_float64array;
  case napi_bigint64_array:
    return js_bigint64array;
  case napi_biguint64_array:
    return js_biguint64array;
  }
}

static inline napi_typedarray_type
js_convert_to_typedarray_type(js_typedarray_type_t type) {
  switch (type) {
  case js_int8array:
    return napi_int8_array;
  case js_uint8array:
  default:
    return napi_uint8_array;
  case js_uint8clampedarray:
    return napi_uint8_clamped_array;
  case js_int16array:
    return napi_int16_array;
  case js_uint16array:
    return napi_uint16_array;
  case js_int32array:
    return napi_int32_array;
  case js_uint32array:
    return napi_uint32_array;
  case js_float32array:
    return napi_float32_array;
  case js_float64array:
    return napi_float64_array;
  case js_bigint64array:
    return napi_bigint64_array;
  case js_biguint64array:
    return napi_biguint64_array;
  }
}

static inline napi_threadsafe_function_release_mode
js_convert_to_threadsafe_function_release_mode(js_threadsafe_function_release_mode_t mode) {
  switch (mode) {
  case js_threadsafe_function_release:
  default:
    return napi_tsfn_release;
  case js_threadsafe_function_abort:
    return napi_tsfn_abort;
  }
}

static inline napi_threadsafe_function_call_mode
js_convert_to_threadsafe_function_call_mode(js_threadsafe_function_call_mode_t mode) {
  switch (mode) {
  case js_threadsafe_function_nonblocking:
  default:
    return napi_tsfn_nonblocking;
  case js_threadsafe_function_blocking:
    return napi_tsfn_blocking;
  }
}

static inline int
js_convert_from_threadsafe_function_status(napi_status status) {
  switch (status) {
  case napi_ok:
    return 0;
  case napi_closing:
    return js_closing;
  case napi_queue_full:
    return js_queue_full;
  default:
    return js_invalid_state;
  }
}

static inline napi_property_descriptor *
js_convert_to_property_descriptors(const js_property_descriptor_t properties[], size_t len) {
  napi_property_descriptor *result = malloc(sizeof(*result) * len);

  if (result == NULL) return NULL;

  for (size_t i = 0; i < len; i++) {
    const js_property_descriptor_t *property = &properties[i];

    result[i] = (napi_property_descriptor) {
      .name = property->name,
      .method = property->method,
      .getter = property->getter,
      .setter = property->setter,
      .value = property->value,
      .attributes = (napi_property_attributes) property->attributes,
      .data = property->data,
    };
  }

  return result;
}

#endif // NAPISH_NAPI_H
