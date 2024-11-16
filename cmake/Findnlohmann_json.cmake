include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT nlohmann_json_INCLUDE_DIR)
  set(nlohmann_json_INCLUDE_DIR /home/restir/restir/builds/json/include/nlohmann)
endif()

find_package_handle_standard_args(nlohmann_json DEFAULT_MSG nlohmann_json_INCLUDE_DIR)
mark_as_advanced(nlohmann_json_INCLUDE_DIR)
