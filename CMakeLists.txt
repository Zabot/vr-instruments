cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project( main )

include_directories("source")
file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable( vrinst ${SOURCES} )
target_link_libraries( vrinst portmidi )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

