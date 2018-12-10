cmake_minimum_required(VERSION 2.8)

project(symreader)

if (WIN32)
	include_directories(./linux-include)
	add_definitions(-D__signed=signed)
endif()

set(SYMREADER_SOURCES
	main.cpp
	sym-elf.cpp
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -frtti")
endif()

if (WIN32)
	set(SYMREADER_SOURCES ${SYMREADER_SOURCES}
		filemapping_win32.cpp
	)	
elseif (UNIX)
	set(SYMREADER_SOURCES ${SYMREADER_SOURCES}
		filemapping_unix.cpp
	)		
endif()

add_executable(symreader ${SYMREADER_SOURCES})
