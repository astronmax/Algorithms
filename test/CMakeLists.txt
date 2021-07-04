cmake_minimum_required(VERSION 3.0)
project(algorithms_test)

set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)
set(LIB_MODULES  ${LIB_MODULES} ${LIB_DIR}/data_structures)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
foreach(test_src ${TEST_SOURCES})
    string(REPLACE ".cpp" "" test ${test_src})
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" test ${test})
    add_executable(${test} ${test_src})
    target_compile_features(${test} PRIVATE cxx_std_17)
    target_compile_options(${test} PRIVATE -Wall -Wextra -g)
    target_include_directories(${test} PRIVATE ${LIB_MODULES})
    target_link_libraries(${test} gtest gtest_main)

    add_test(${test} ${test})
endforeach(test_src ${TEST_SOURCES})