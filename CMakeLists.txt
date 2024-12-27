cmake_minimum_required(VERSION 3.31)
project(cclox)
add_definitions(-ftime-trace)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
