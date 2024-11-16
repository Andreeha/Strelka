include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
include(${CMAKE_ROOT}/Modules/SelectLibraryConfigurations.cmake)

if(NOT doctest_INCLUDE_DIR)
  set(doctest_INCLUDE_DIR /home/restir/restir/builds/doctest/doctest)
endif()

find_package_handle_standard_args(doctest DEFAULT_MSG doctest_INCLUDE_DIR)
mark_as_advanced(doctest_INCLUDE_DIR)
