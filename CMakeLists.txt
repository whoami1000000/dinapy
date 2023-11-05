cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 23)
include_directories("${CMAKE_SOURCE_DIR}/src")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(App "Build app" OFF)
if (App)
    list(APPEND VCPKG_MANIFEST_FEATURES "app")
endif ()

option(Test "Build all tests" OFF)
if (Test)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
    enable_testing()
endif ()

option(Py "Build python package" OFF)
if (Py)
    list(APPEND VCPKG_MANIFEST_FEATURES "py")
endif ()

include(JSONParser)
file(READ "${CMAKE_SOURCE_DIR}/vcpkg.json" VCPKG_CONTENT)
sbeParseJson(VCPKG_JSON VCPKG_CONTENT)
project(dina VERSION ${VCPKG_JSON.version-string})

configure_file(
        "${CMAKE_SOURCE_DIR}/version.h.in"
        "${CMAKE_BINARY_DIR}/version.h"
        @ONLY)

add_subdirectory(src)

if (App)
    install(TARGETS dina_app)
endif ()
install(TARGETS dina)
include(Packing)

