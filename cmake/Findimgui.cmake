include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT imgui_INCLUDE_DIR)
  set(imgui_INCLUDE_DIR /home/restir/restir/builds/imgui)
endif()

find_package_handle_standard_args(imgui DEFAULT_MSG imgui_INCLUDE_DIR)
mark_as_advanced(imgui_INCLUDE_DIR)
