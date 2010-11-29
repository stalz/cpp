cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project("ap")

if(WIN32)
    add_definitions("/W4 /MP3")
else()
    add_definitions("-std=c++0x -pedantic -Wall -Wextra -Wfatal-errors -Wswitch-default -Wswitch-enum -Wunused-parameter -Wfloat-equal -Wundef -Wstrict-null-sentinel")
endif()

#include_directories(${include_directories} .)
#link_directories(${link_directories} .)

add_executable(main main.cpp)

target_link_libraries(main)
