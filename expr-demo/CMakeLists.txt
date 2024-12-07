cmake_minimum_required(VERSION 3.16)

#project(expr_demo)

message(" ~~ expr_demo cmake..")

add_executable(expr_demo 
    main.cpp 
)

target_include_directories(expr_demo PRIVATE src)


