cmake_minimum_required(VERSION 3.14)
project(roverlib-c VERSION 1.0 LANGUAGES C)

# Find cJSON
find_path(CJSON_INCLUDE_DIR cJSON.h
    HINT /usr/include/cjson
)
find_library(CJSON_LIBRARY cjson)

if(NOT CJSON_INCLUDE_DIR OR NOT CJSON_LIBRARY)
    message(FATAL_ERROR "cJSON not found. Please install libcjson-dev.")
endif()
# Include directories for cJSON
include_directories(${CJSON_INCLUDE_DIR})

# Check if protobuf-c is installed
find_path(PROTOBUF_C_INCLUDE_DIR protobuf-c/protobuf-c.h)
find_library(PROTOBUF_C_LIBRARY protobuf-c)

if(NOT PROTOBUF_C_INCLUDE_DIR OR NOT PROTOBUF_C_LIBRARY)
    message(FATAL_ERROR "protobuf-c not found. Please install libprotobuf-c-dev.")
endif()

# Check if ZeroMQ is installed
find_path(ZMQ_INCLUDE_DIR zmq.h)
find_library(ZMQ_LIBRARY zmq)

if(NOT ZMQ_INCLUDE_DIR OR NOT ZMQ_LIBRARY)
    message(FATAL_ERROR "ZeroMQ not found. Please install libzmq3-dev.")
endif()

# Dependencies
add_subdirectory(deps/c-list)         # Build c-list static library
add_subdirectory(deps/c-hashtable)   # Build c-hashtable static library

# Include directories
include_directories(include)
include_directories(deps/c-list/include deps/c-hashtable/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/rovercom)

# Add include paths for public headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Library sources
file(GLOB_RECURSE SOURCES src/*.c)

# Add shared library
add_library(roverlib-c SHARED ${SOURCES})

# Link against dependencies
target_link_libraries(roverlib-c
    ${CJSON_LIBRARY}
    pthread
    protobuf-c
    zmq
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/c-list/build/liblist.a
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/c-hashtable/build/libhashtable.a
)

# Installation
install(TARGETS roverlib-c LIBRARY DESTINATION lib)
install(FILES include/roverlib.h DESTINATION include)
install(DIRECTORY include/rovercom DESTINATION include)
install(DIRECTORY include/roverlib DESTINATION include)