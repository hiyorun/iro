file(GLOB_RECURSE LIBRARY_SOURCES
    "*.cc"
)

add_library(MaterialColorUtility STATIC ${LIBRARY_SOURCES})

target_include_directories(MaterialColorUtility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
