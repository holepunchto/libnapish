cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-harden REQUIRED PATHS node_modules/cmake-harden)
find_package(cmake-napi REQUIRED PATHS node_modules/cmake-napi)
find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(napish LANGUAGES C VERSION 0.0.0)

fetch_package("github:holepunchto/libutf")

download_node_headers(node_headers)

add_library_targets(
  napish
  HEADERS
    include/bare.h
    include/bare/module.h
    include/js.h
  FEATURES
    c_std_11
  SOURCES
    src/bare/module.c
    src/js.c
    src/napi.h
    src/sharedarraybuffer.c
  LINK
    utf::headers
  TYPE
    STATIC
)

harden(napish)

target_include_directories(
  napish
  PRIVATE
    ${node_headers}
)

add_test_subdirectory(test)
