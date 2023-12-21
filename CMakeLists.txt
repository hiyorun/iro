cmake_minimum_required(VERSION 3.12)
project(iroha)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(externals/google-mcu)

file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(iroha ${SRCFILES})

find_package(absl CONFIG REQUIRED)

target_link_libraries(iroha PRIVATE MaterialColorUtility absl::flat_hash_map)
