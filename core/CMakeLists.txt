cmake_minimum_required(VERSION 3.15)
project(compiler_parser_simulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(parser_core ${SOURCES})