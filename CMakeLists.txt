cmake_minimum_required(VERSION 3.11)
project(III-Rainbomizer)

set (CMAKE_CXX_STANDARD 17)

# C++20
if (MSVC_VERSION GREATER_EQUAL "1900")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  # Because CMAKE_MSVC_RUNTIME_LIBRARY doesn't work for whatever reason
  set(CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
    )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
endif()


# plugin-sdk
include(FetchContent)
FetchContent_Declare(plugin-sdk
  GIT_REPOSITORY https://github.com/gta-chaos-mod/plugin-sdk
  GIT_SHALLOW)
FetchContent_MakeAvailable(plugin-sdk)

set_target_properties(
  plugin_vc plugin_sa
  PROPERTIES EXCLUDE_FROM_ALL true)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_library("gta3_rbmzr" SHARED ${SOURCES})

set_target_properties("gta3_rbmzr" PROPERTIES SUFFIX ".asi")
target_link_libraries("gta3_rbmzr" PUBLIC plugin_III)
target_compile_definitions("gta3_rbmzr" PUBLIC NOMINMAX)

