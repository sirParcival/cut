cmake_minimum_required(VERSION 3.20)
project(cut C)

set(CMAKE_C_STANDARD 99)

add_executable(cut tests.c threads.c threads.h ring_buffer.c ring_buffer.h)
target_link_libraries( cut pthread )