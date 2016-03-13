project (frhed CXX)

#######################
# cmake settings
#######################

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake")
cmake_minimum_required (VERSION 2.8.11)

# In-source builds are disabled.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
        "CMake generation is not possible within the source directory!"
        "\n Remove the CMakeCache.txt file and try again from another folder, e.g.:"
        "\n "
        "\n rm CMakeCache.txt"
        "\n mkdir build"
        "\n cd build"
        "\n cmake .."
    )
endif()

#######################
# project
#######################

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
include_directories ("${PROJECT_SOURCE_DIR}/src/heksedit")
include_directories ("${PROJECT_SOURCE_DIR}/src/frhed")

#######################
# heksedit
#######################

file(GLOB heksedit_src
    "src/heksedit/MAUtil/*.cpp"
    "src/heksedit/*.cpp"
)

file(GLOB heksedit_hdr
    "src/heksedit/MAUtil/*.h"
    "src/heksedit/*.h"
)

file(GLOB heksedit_res
    "src/heksedit/*.rc"
)

add_library (heksedit SHARED ${heksedit_src} ${heksedit_hdr} ${heksedit_res})
target_link_libraries (heksedit version comctl32 wininet shlwapi Htmlhelp)
set_target_properties (heksedit PROPERTIES OUTPUT_NAME hekseditU)

#######################
# frhed
#######################

file(GLOB frhed_src
    "src/frhed/*.cpp"
)

file(GLOB frhed_hdr
    "src/frhed/*.h"
)

file(GLOB frhed_res
    "src/frhed/*.rc"
)

add_executable (frhed ${frhed_src} ${frhed_hdr} ${frhed_res})
target_link_libraries (frhed version comctl32 wininet shlwapi Htmlhelp)
set_target_properties (frhed PROPERTIES OUTPUT_NAME frhed)
set_target_properties(frhed PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
set_target_properties(frhed PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
set_target_properties(frhed PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
set_target_properties(frhed PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
    