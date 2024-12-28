# @file      CMakeLists.txt
# @brief     c-hashtable library CMakeLists file
#
# This is a slightly modified version of the original CMakeLists.txt file by joelguittet
# to add a static library target, which can be in turn compiled by the roverlib-c library to a shared object.
# the original source code can be found at https://github.com/joelguittet/c-hashtable
#
# MIT License
#
# Copyright (c) 2021-2023 joelguittet and c-hashtable contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# CMake minimum version
cmake_minimum_required(VERSION 3.14)

# Project name
project(c-hashtable)

# Project version
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/VERSION PROJECT_VER LIMIT_COUNT 1)
string(REPLACE "." ";" PROJECT_VER_LIST ${PROJECT_VER})
list(GET PROJECT_VER_LIST 0 PROJECT_VER_MAJOR)
list(GET PROJECT_VER_LIST 1 PROJECT_VER_MINOR)
list(GET PROJECT_VER_LIST 2 PROJECT_VER_PATCH)

# Use GNU installation directories
include(GNUInstallDirs)

# Additional flags
set(c_flags "${c_flags} -Os -ffunction-sections -Wall -fPIC")
set(linker_flags "${linker_flags} -Wl,-gc-sections")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")

# Definitions
add_definitions(-DHASHTABLE_EXPORT_SYMBOLS -DHASHTABLE_API_VISIBILITY)

# CMake subdirectories
if(NOT TARGET amp)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/amp/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/amp)
    endif()
endif()
if(NOT TARGET axon)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/axon/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/axon)
    endif()
endif()
if(NOT TARGET discover)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/discover/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/discover)
    endif()
endif()

# List of sources
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/amp/include)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/amp/include)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/amp/lib/cJSON/cJSON.h)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/amp/lib/cJSON)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/axon/include)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/axon/include)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/discover/include)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/discover/include)
endif()

# Creation of the shared library
add_library(hashtable SHARED ${src})

# Creation of the static library
add_library(hashtable_static STATIC ${src})

# Link the libraries with the wanted libraries
target_link_libraries(hashtable pthread)
target_link_libraries(hashtable_static pthread)

# Properties of the shared library
set_target_properties(hashtable
    PROPERTIES
    SOVERSION "${PROJECT_VER_MAJOR}"
    VERSION "${PROJECT_VER_MAJOR}.${PROJECT_VER_MINOR}.${PROJECT_VER_PATCH}"
)

# Properties of the static library
set_target_properties(hashtable_static
    PROPERTIES
    OUTPUT_NAME "hashtable"  # Ensures both libraries have the same base name
)

# Installation of headers
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/hashtable.h DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}")

# Installation of the shared and static libraries
install(TARGETS hashtable hashtable_static
    ARCHIVE DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"  # For static library
    LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"  # For shared library
    RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_BINDIR}"  # For executables (if any)
    INCLUDES DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
)

# Creation of the examples binaries
option(ENABLE_HASHTABLE_EXAMPLES "Enable building hashtable examples" OFF)
if(ENABLE_HASHTABLE_EXAMPLES)
    add_executable(hashtable_basic ${CMAKE_CURRENT_SOURCE_DIR}/examples/hashtable_basic.c)
    target_link_libraries(hashtable_basic hashtable)
    install(TARGETS hashtable_basic
        RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_BINDIR}"
    )
endif()
