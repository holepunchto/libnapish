enable_language(CXX)

function(add_addon_test)
  add_napi_module(addon INSTALL OFF)

  target_sources(
    ${addon}
    PRIVATE
      ${ARGN}
  )

  target_link_libraries(
    ${addon}
    PRIVATE
      napish::static
  )

  cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME name)

  add_test_script(
    ${name}
    test.js
    RUNNER node
    ARGS $<TARGET_FILE:${addon}_module>
  )
endfunction()

add_subdirectory(module)
add_subdirectory(module-cxx)
add_subdirectory(sharedarraybuffer)
add_subdirectory(threadsafe-function)

# The test registers its module from a constructor, which MSVC has no attribute
# for.
if(NOT MSVC)
  add_subdirectory(module-register)
endif()
