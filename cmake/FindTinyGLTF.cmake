include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT TinyGLTF_INCLUDE_DIR)
  set(TinyGLTF_INCLUDE_DIR /home/restir/restir/builds/tinygltf)
endif()

find_package_handle_standard_args(TinyGLTF DEFAULT_MSG TinyGLTF_INCLUDE_DIR)
mark_as_advanced(TinyGLTF_INCLUDE_DIR)
