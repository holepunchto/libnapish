# libnapish

Implementation of the [`libjs`](https://github.com/holepunchto/libjs) and [Bare](https://github.com/holepunchto/bare) native addon APIs on top of [Node-API](https://nodejs.org/api/n-api.html). It lets addons written for Bare build as Node.js addons from the same source.

## Usage

Link the static library into a Node-API module, such as one created with [`cmake-napi`](https://github.com/holepunchto/cmake-napi):

```cmake
add_napi_module(addon)

target_link_libraries(
  ${addon}
  PRIVATE
    napish::static
)
```

Modules then register themselves with `BARE_MODULE()` from `<bare.h>` and use the `js_*()` functions from `<js.h>`, just as they would in Bare.

The library targets Node-API version 10, which is available from Node.js 22.14. The `SharedArrayBuffer` functions use experimental Node-API functions and so need a Node.js that provides them, but only modules that use them are affected.

The `js.h` types are the Node-API types, so the two APIs can be mixed freely in the same module.

## API

See [`include/js.h`](include/js.h) and [`include/bare/module.h`](include/bare/module.h) for the public API.

## License

Apache-2.0
