cmake_minimum_required(VERSION 3.16)
project(MY_LIBRARY C)

set(CMAKE_C_STANDARD 99)

add_executable(MY_LIBRARY user.c HashMap_Rehashing/library_HashMap.c HashMap_Rehashing/library_HashMap.h BinaryTree/library_Tree.c BinaryTree/library_Tree.h user_tree.c)
