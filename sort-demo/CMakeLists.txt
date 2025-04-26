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






# Add tests


#next line: build googletest with dynamically-linked Runtime
set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" )

add_subdirectory(C:/Soft/googletest googletest)

add_executable(runGtests test/mysort-test.cpp)
target_include_directories(runGtests PRIVATE src ../googletest/googletest/include)
target_link_libraries(runGtests mysort gtest)



#-----------

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


#--------------------

set (CATCH2_DIR ../external/catch2)
add_executable(runCatch2tests 
    test/mysort-catch2test.cpp
    ${CATCH2_DIR}/extras/catch_amalgamated.cpp
)
target_include_directories(runCatch2tests PRIVATE src ${CATCH2_DIR})
target_link_libraries(runCatch2tests mysort)


enable_testing()




add_test(NAME MyGTests COMMAND runGtests)
add_test(NAME MyDoctests COMMAND runDoctests)
add_test(NAME MyCatch2tests COMMAND runCatch2tests)


add_custom_command(TARGET runCatch2tests
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)
