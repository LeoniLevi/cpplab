cmake_minimum_required(VERSION 3.16)

project(sort_demo)
set(CMAKE_CXX_STANDARD 17)

add_library(mysort 
    src/myqsort.cpp
    src/mymergesort.cpp 
    src/myheapsort.cpp
    src/myutil.cpp
)

add_executable(sort_demo main.cpp)

target_include_directories(sort_demo PRIVATE src)
target_link_libraries(sort_demo mysort)

#next line: build googletest with dynamically-linked Runtime
set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )

add_subdirectory(C:/Soft/googletest googletest)

add_executable(runTests test/mysort-test.cpp)
target_include_directories(runTests PRIVATE src ../googletest/googletest/include)
target_link_libraries(runTests mysort gtest)


# Add Doctest as a dependency
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11 # Use the latest stable version
)
FetchContent_MakeAvailable(doctest)

add_executable(runDoctests test/mysort-doctest.cpp)
target_include_directories(runDoctests PRIVATE src)
target_link_libraries(runDoctests mysort doctest::doctest)


enable_testing()

# Add tests
add_test(NAME MyTests COMMAND runTests)

add_custom_command(TARGET runTests
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)

add_test(NAME MyDoctests COMMAND runDoctests)

add_custom_command(TARGET runDoctests
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)



