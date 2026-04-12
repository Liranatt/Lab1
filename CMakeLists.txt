cmake_minimum_required(VERSION 3.28)
project(Lab1 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -g")

add_executable(task0 count_words.c)
add_executable(task1 adresses.c)
add_executable(task2 base.c)
