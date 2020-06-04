cmake_minimum_required(VERSION 3.16)
project(MY_LIBRARY C)

set(CMAKE_C_STANDARD 99)

add_executable(MY_LIBRARY users/user_circleLickedList.c CircleList/library_CircleList.c CircleList/library_CircleList.h)
