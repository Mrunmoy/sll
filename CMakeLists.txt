cmake_minimum_required(VERSION 3.13)
project(singly_ll C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(singly_ll src/sll.c inc/sll.h test/test.c)