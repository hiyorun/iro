cmake_minimum_required(VERSION 3.12)
project(iro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/google-mcu)

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(iro ${SRCFILES})

find_package(absl CONFIG REQUIRED)

target_link_libraries(iro PRIVATE MaterialColorUtility absl::flat_hash_map)
