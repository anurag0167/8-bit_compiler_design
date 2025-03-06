cmake_minimum_required(VERSION 3.20)
set(PROJECT 8_bit_compiler)
project(${PROJECT} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Copy `compile_commands.json` from CMAKE_BINARY_DIR to CMAKE_SOURCE_DIR
if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/compile_commands.json"
        "${CMAKE_SOURCE_DIR}/compile_commands.json")
endif()

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT} ${SOURCES})

target_include_directories(
    ${PROJECT} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)