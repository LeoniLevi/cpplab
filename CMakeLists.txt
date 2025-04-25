cmake_minimum_required(VERSION 3.16)

project(cpplab)
set(CMAKE_CXX_STANDARD 17)

# targets a multi-threaded statically-linked runtime library 
# with or without debug information depending on the configuration.
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# next is the default 
# targets a multi-threaded dynamically-linked runtime library 
#set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>DLL)

add_subdirectory(BinaryTree)
#add_subdirectory(expr-demo)
add_subdirectory(sort-demo)

message(" ~~ CMAKE_CXX_COMPILE_FEATURES: ${CMAKE_CXX_COMPILE_FEATURES}")
if("cxx_std_20" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    add_subdirectory(cpp20-demo)
endif()
