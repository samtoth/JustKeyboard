cmake_minimum_required(VERSION 3.16)
project(JustKeyboard)

set(CMAKE_CXX_STANDARD 14)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    message(FATAL_ERROR "This is a big-endian system and is not supported")
else()
    message(STATUS "Little endian system")
endif()

set(CMAKE_CXX_FLAGS "-Wall -D__LINUX_ALSA__ -D__LITTLE_ENDIAN__")

set(CMAKE_INCLUDE_CURRENT_DIR  ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(src)
