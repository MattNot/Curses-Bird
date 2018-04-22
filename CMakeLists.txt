project(cursesbird)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE 1)
find_package(Curses REQUIRED)
include_directories(includes ${CURSES_INCLUDE_DIR})
file(GLOB SOURCES "src/*.cpp")
add_executable(cursesbird ${SOURCES})
target_link_libraries(cursesbird ${CURSES_LIBRARIES})

