cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)

project(cpp20_demo)

message (" ~~ cpp23_demo building...")

if (UNIX)
    #set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
    #set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
    message("~~ CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
endif()


if (MSVC)
    #add_compile_options("-std:c++latest")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    #set(CMAKE_CXX_STANDARD 20)
    #add_compile_options(-fcoroutines)
endif()

#add_compile_definitions(USE_CPP20_RANGES)
#add_compile_definitions(USE_CPP17_FILESYSTEM)

option(BUILD_COROUTINES "Build coroutione c++20 related code" ON)

if (BUILD_COROUTINES)
    add_compile_definitions(USE_CPP20_COROUTINES)
endif()
    



message("~~ CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message("~~ CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message("~~ CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("~~ UNIX: ${UNIX}")
message("~~ MSVC: ${MSVC}")


#- sources ddd ggg MSVC-sources sources
set (sources
    main.cpp
    src/fsplay.cpp
    src/rngplay.cpp
    src/coroplay.cpp

    src/conceptplay.cpp
    src/concept_play_monadic.cpp
)

add_executable(cpp20_demo ${sources} )

target_include_directories(cpp20_demo PRIVATE src ../Common)
if (UNIX)
    target_link_libraries(cpp20_demo pthread)
endif()
