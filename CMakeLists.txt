cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
project( main )

include_directories("source")
file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable( vrinst ${SOURCES} )

# Libraries

# PortMIDI for midi interface
target_link_libraries( vrinst portmidi )

# Leap SDK
include_directories("$ENV{LEAP_SDK}/include")
link_directories("$ENV{LEAP_SDK}/lib/x64")

if(UNIX)
	if(NOT APPLE)
		target_link_libraries( vrinst "$ENV{LEAP_SDK}/lib/x64/libLeap.so" )
	endif(NOT APPLE)
endif(UNIX)

if(WIN32)
	target_link_libraries( vrinst "$ENV{LEAP_SDK}/lib/x64/Leap.lib" )
endif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

