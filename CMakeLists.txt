cmake_minimum_required(VERSION 3.16)
project(MY_LIBRARY C)

set(CMAKE_C_STANDARD 99)

add_executable(MY_LIBRARY CircleList/library_CircleList.c CircleList/library_CircleList.h user.c HaxhMap/library_HashMap.c HaxhMap/library_HashMap.h Array/library_Array.c Array/library_Array.h)
