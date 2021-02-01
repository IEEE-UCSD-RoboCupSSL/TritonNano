cmake_minimum_required(VERSION 3.16)
project(TritonNano C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/nanopb-0.4.4-linux-x86/extra)
find_package(Nanopb REQUIRED)
include_directories(${NANOPB_INCLUDE_DIRS})

nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS RELPATH proto proto/NanoCmdAPI.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(proto DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})
set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -O0")

add_executable(TritonNano main.c ${PROTO_SRCS} ${PROTO_HDRS})