cmake_minimum_required(VERSION 3.16)

project(sort_demo)

add_executable(sort_demo 
    main.cpp 
    src/myqsort.cpp
    src/mymergesort.cpp 
    src/myheapsort.cpp
    src/myutil.cpp
)

target_include_directories(sort_demo PRIVATE src)


