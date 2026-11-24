#include <bare.h>
#include <stdlib.h>

#include "../napi.h"

void
bare_module_register(bare_module_t *module) {
  // Node.js keeps a pointer to the module and only calls its register function
  // once the addon has loaded, so the module must outlive this call.
  napi_module *napi_module = malloc(sizeof(*napi_module));

  *napi_module = (struct napi_module){
    .nm_version = NAPI_MODULE_VERSION,
    .nm_register_func = module->exports,
    .nm_modname = module->name,
  };

  napi_module_register(napi_module);
}
