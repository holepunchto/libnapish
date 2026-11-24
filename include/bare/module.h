#ifndef BARE_MODULE_H
#define BARE_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <js.h>
#include <stdint.h>

#define BARE_MODULE_VERSION 0

/**
 * The Node-API version that modules are built against and report to Node.js.
 */
#define BARE_MODULE_NAPI_VERSION 10

#ifdef __cplusplus
#define BARE_MODULE_EXTERN_C extern "C"
#else
#define BARE_MODULE_EXTERN_C
#endif

#ifdef _WIN32
#define BARE_MODULE_EXPORT __declspec(dllexport)
#else
#define BARE_MODULE_EXPORT __attribute__((visibility("default")))
#endif

#define BARE_MODULE(id, fn) \
  BARE_MODULE_EXTERN_C BARE_MODULE_EXPORT int32_t node_api_module_get_api_version_v1(void) { \
    return BARE_MODULE_NAPI_VERSION; \
  } \
  BARE_MODULE_EXTERN_C BARE_MODULE_EXPORT js_value_t *napi_register_module_v1(js_env_t *env, js_value_t *exports) { \
    return fn(env, exports); \
  }

typedef struct bare_module_s bare_module_t;

typedef js_value_t *(*bare_module_register_cb)(js_env_t *env, js_value_t *exports);

/** @version 0 */
struct bare_module_s {
  int version;

  /** @since 0 */
  const char *name;

  /** @since 0 */
  bare_module_register_cb exports;
};

void
bare_module_register(bare_module_t *module);

#ifdef __cplusplus
}
#endif

#endif // BARE_MODULE_H
