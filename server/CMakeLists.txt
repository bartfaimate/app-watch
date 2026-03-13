cmake_minimum_required(VERSION 3.16)

# debug symbols
set(CMAKE_BUILD_TYPE Debug)
project("server-daemon")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(/usr/include/)

set(SOURCES src/main.c src/network.c src/apps.c src/string_utils.c)

enable_testing()


set(CMAKE_CXX_STANDARD 14)
add_executable(server-daemon ${SOURCES})


#
# ---- tests ----
#

add_executable(test_string_utils
    tests/test_string_utils.c
    src/string_utils.c
)

include_directories(/usr/include/
src/
)



add_test(
    NAME string_utils_test
    COMMAND test_string_utils
)