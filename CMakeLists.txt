cmake_minimum_required(VERSION 3.17)
project(C_cw1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_cw1
        book_management.h
        function.c
        main.c)
