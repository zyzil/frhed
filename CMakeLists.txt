project (zhed CXX)

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

add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
include_directories ("${PROJECT_SOURCE_DIR}/src/zhed")

#######################
# zhed
#######################

file(GLOB zhed_src
	"src/zhed/MAUtil/*.cpp"
    "src/zhed/*.cpp"
)

file(GLOB zhed_hdr
	"src/zhed/MAUtil/*.h"
    "src/zhed/*.h"
)

file(GLOB zhed_res
    "src/zhed/*.rc"
)

MESSAGE( STATUS "Use STATIC runtime" )
set(NAME_RT MT)
set (CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
set (CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set (CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set (CMAKE_C_FLAGS_MINSIZEREL       "${CMAKE_C_FLAGS_MINSIZEREL} /MT")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MT")
set (CMAKE_C_FLAGS_RELEASE          "${CMAKE_C_FLAGS_RELEASE} /MT")
set (CMAKE_C_FLAGS_DEBUG            "${CMAKE_C_FLAGS_DEBUG} /MTd")

add_executable (zhed ${zhed_src} ${zhed_hdr} ${zhed_res})
target_link_libraries (zhed version comctl32 wininet shlwapi Htmlhelp)
set_target_properties(zhed PROPERTIES COMPILE_FLAGS "/Yuprecomp.h")
set_source_files_properties(src/zhed/precomp.cpp PROPERTIES COMPILE_FLAGS "/Ycprecomp.h")
set_target_properties (zhed PROPERTIES OUTPUT_NAME zhed)
set_target_properties(zhed PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
set_target_properties(zhed PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
set_target_properties(zhed PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
set_target_properties(zhed PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
    