cmake_minimum_required(VERSION 3.10.2)
project(cclox)
add_definitions(-ftime-trace)
set(CMAKE_UNITY_BUILD TRUE)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
