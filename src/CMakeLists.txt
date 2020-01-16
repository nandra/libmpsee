cmake_minimum_required(VERSION 3.0)
project (libmpsse)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

include (FindPkgConfig)

find_library(FTDI_LIBRARY ftdi1)
pkg_search_module(FTDI libftdi1)
include_directories( ${FTDI_INCLUDEDIR} )

# source files for library
file(GLOB LIB_MPSSE_SRC ./*.c ./*.h)

set(PACKAGE_VERSION "1.3")
add_definitions(-DPACKAGE_VERSION="${PACKAGE_VERSION}")

# build shared library
add_library(libmpsse SHARED ${LIB_MPSSE_SRC})
set_target_properties(libmpsse PROPERTIES
    VERSION ${PACKAGE_VERSION}
    SOVERSION 1
    PUBLIC_HEADER mpsse.h)

# build examples
add_subdirectory(examples)

# testing
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/cmake-template/cmake/Modules")

# cmocka
option(ENABLE_TESTS "Perform unit tests after build" ON)
if (ENABLE_TESTS)
    find_package(CMocka CONFIG REQUIRED)
    include(AddCMockaTest)
    include(AddMockedTest)
    add_subdirectory(test)
    enable_testing()
endif(ENABLE_TESTS)
