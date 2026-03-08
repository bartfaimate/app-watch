cmake_minimum_required(VERSION 3.16)

project("server-daemon")

set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(/usr/include/)

set(SOURCES src/main.c src/network.c src/apps.c)

set (CMAKE_CXX_STANDARD 14)
add_executable(server-daemon ${SOURCES})