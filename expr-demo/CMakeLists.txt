cmake_minimum_required(VERSION 3.16)

project(expr_demo CXX C)

message(" ~~ expr_demo cmake..")

add_executable(expr_demo 
    main.cpp 
    ../cpputil/IntKeyValueDbMap.cpp
    ../external/sqlite3/sqlite3.c
)

target_include_directories(expr_demo PRIVATE ../cpputil ../external/sqlite3)


