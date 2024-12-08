cmake_minimum_required(VERSION 3.10)

project(cpplab)

add_subdirectory(BinaryTree)
add_subdirectory(expr-demo)
add_subdirectory(sort-demo)

message(" ~~ CMAKE_CXX_COMPILE_FEATURES: ${CMAKE_CXX_COMPILE_FEATURES}")

if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    add_subdirectory(cpp20-demo)
endif()