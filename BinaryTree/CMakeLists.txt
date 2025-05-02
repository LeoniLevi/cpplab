cmake_minimum_required(VERSION 3.16)

project(BinaryTree)

add_executable(tree_test 
    main.cpp 
    src/red-black/rbint_tree.cpp
    src/avl/avl_tree.cpp
    src/binary_tree.cpp 
    src/avl/bdl_tree.hpp
    src/avl/bdl_tree.cpp

    src/legacy/_bst_node.cpp 
    src/legacy/_bin_tree.cpp
    src/legacy/_my_bin_tree.cpp 
    src/red-black/rbq_int_tree.cpp 
    src/util.cpp)

target_include_directories(tree_test PRIVATE src)


