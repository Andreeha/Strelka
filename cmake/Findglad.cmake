include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT glad_INCLUDE_DIR)
  set(glad_INCLUDE_DIR /home/restir/restir/builds/Strelka/external/glad)
endif()

find_package_handle_standard_args(glad DEFAULT_MSG glad_INCLUDE_DIR)
mark_as_advanced(glad_INCLUDE_DIR)
