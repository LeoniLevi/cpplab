cmake_minimum_required(VERSION 3.16)

project(BinaryTree)

add_executable(tree_test 
    main.cpp 
    src/avl_tree.cpp
    src/binary_tree.cpp 
    src/bdl_tree.hpp
    src/bdl_tree.cpp
    src/_bst_node.cpp 
    src/_bin_tree.cpp
    src/_my_bin_tree.cpp)

target_include_directories(tree_test PRIVATE src)


