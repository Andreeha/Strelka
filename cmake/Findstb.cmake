include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT Stb_INCLUDE_DIR)
  set(Stb_INCLUDE_DIR /home/restir/restir/builds/stb)
endif()

find_package_handle_standard_args(Stb DEFAULT_MSG Stb_INCLUDE_DIR)
mark_as_advanced(Stb_INCLUDE_DIR)
