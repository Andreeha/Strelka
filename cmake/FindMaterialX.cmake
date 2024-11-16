include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT MaterialX_INCLUDE_DIR)
  set(MaterialX_ROOT_DIR /home/restir/restir/builds/OpenUSD_no_python)
  set(MaterialX_INCLUDE_DIR /home/restir/restir/builds/OpenUSD_no_python/include)
  set(MaterialX_INCLUDE /home/restir/restir/builds/OpenUSD_no_python/include)
  set(MaterialX_LIB_DIR /home/restir/restir/builds/OpenUSD_no_python/lib)
endif()

find_package_handle_standard_args(MaterialX DEFAULT_MSG MaterialX_ROOT_DIR)
mark_as_advanced(MaterialX_ROOT_DIR)
