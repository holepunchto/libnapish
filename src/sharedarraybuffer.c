// The SharedArrayBuffer functions of Node-API are still experimental, so they
// are kept apart to only be linked, and so require a Node.js that has them,
// when they are used.
#define NAPI_EXPERIMENTAL

#include <js.h>

#include "napi.h"

int
js_create_sharedarraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result) {
  napi_status status = node_api_create_sharedarraybuffer(env, len, data, result);
  return js_convert_from_status(status);
}

int
js_create_unsafe_sharedarraybuffer(js_env_t *env, size_t len, void **data, js_value_t **result) {
  return js_create_sharedarraybuffer(env, len, data, result);
}

int
js_is_sharedarraybuffer(js_env_t *env, js_value_t *value, bool *result) {
  napi_status status = node_api_is_sharedarraybuffer(env, value, result);
  return js_convert_from_status(status);
}

int
js_get_sharedarraybuffer_info(js_env_t *env, js_value_t *sharedarraybuffer, void **data, size_t *len) {
  napi_status status = napi_get_arraybuffer_info(env, sharedarraybuffer, data, len);
  return js_convert_from_status(status);
}
