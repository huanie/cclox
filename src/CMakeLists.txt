add_executable(cclox)
add_library(lib SHARED)

target_sources(lib
PUBLIC
${CMAKE_SOURCE_DIR}/src/chunk.cpp
${CMAKE_SOURCE_DIR}/src/chunk.h
${CMAKE_SOURCE_DIR}/src/compiler.cpp
${CMAKE_SOURCE_DIR}/src/compiler.h
${CMAKE_SOURCE_DIR}/src/debug.cpp
${CMAKE_SOURCE_DIR}/src/debug.h
${CMAKE_SOURCE_DIR}/src/error-reporter.cpp
${CMAKE_SOURCE_DIR}/src/error-reporter.h
${CMAKE_SOURCE_DIR}/src/scanner.cpp
${CMAKE_SOURCE_DIR}/src/scanner.h
${CMAKE_SOURCE_DIR}/src/token.h
${CMAKE_SOURCE_DIR}/src/vm.cpp
${CMAKE_SOURCE_DIR}/src/vm.h)

target_sources(cclox
PRIVATE
${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(cclox lib)
