add_executable(cclox)

target_sources(cclox
PUBLIC
FILE_SET CXX_MODULES
FILES
chunk.mpp
compiler.mpp
debug.mpp
error-reporter.mpp
scanner.mpp
token.mpp
vm.mpp
)


target_sources(cclox
PUBLIC
chunk.cpp
compiler.cpp
debug.cpp
error-reporter.cpp
scanner.cpp
vm.cpp)

target_sources(cclox PUBLIC main.cpp)
