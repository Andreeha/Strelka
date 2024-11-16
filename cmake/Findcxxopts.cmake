include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT cxxopts_INCLUDE_DIR)
  set(cxxopts_INCLUDE_DIR /home/restir/restir/builds/cxxopts/include)
endif()

find_package_handle_standard_args(cxxopts DEFAULT_MSG cxxopts_INCLUDE_DIR)
mark_as_advanced(cxxopts_INCLUDE_DIR)
