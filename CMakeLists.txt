cmake_minimum_required(VERSION 3.16)
project(JustKeyboard)

set(CMAKE_CXX_STANDARD 17)


set(QTDIR $ENV{QTDIR} CACHE STRING "Qt install path")
list(APPEND CMAKE_PREFIX_PATH ${QTDIR})
set(QT_MINIMUM_VERSION 5.3.0)

# Test for supported Qt version
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if(QT_VERSION VERSION_LESS QT_MINIMUM_VERSION)
    MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}.
    Installed version: ${QT_VERSION}")
endif()
message(STATUS "Qt version: ${QT_VERSION}")

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

add_subdirectory(thirdparty/stk)
include_directories(thirdparty)

add_subdirectory(src)
