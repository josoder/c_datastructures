cmake_minimum_required(VERSION 3.8)
project(datastructures)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c implementations/bst.c interfaces/bst.h tests/bst_test.h interfaces/rbbst.h implementations/rbbst.c tests/rb_tree_test.h)
add_executable(datastructures ${SOURCE_FILES})