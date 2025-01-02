add_executable(cclox)

target_sources(cclox
PRIVATE
${CMAKE_SOURCE_DIR}/src/main.cpp
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
target_link_libraries(cclox -static -static-libgcc -static-libstdc++)
