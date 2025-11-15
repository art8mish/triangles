cmake_minimum_required(VERSION 3.12)
project(triangles LANGUAGES CXX)
enable_testing()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

find_package(GTest REQUIRED)
 
function(add_warnings target)
    target_compile_options(${target} PRIVATE
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wold-style-cast
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
endfunction()

function(add_proj_exec target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target} PRIVATE ${INCLUDE_DIR})
    target_compile_features(${target} PRIVATE cxx_std_20)
    add_warnings(${target})
endfunction()

function(add_proj_test target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target} PRIVATE ${INCLUDE_DIR})
    target_compile_features(${target} PRIVATE cxx_std_20)
    target_link_libraries(${target} PRIVATE GTest::gtest GTest::gtest_main)
    add_warnings(${target})
    add_test(NAME ${target} COMMAND ${target})
endfunction()


add_proj_exec(triangles ${SRC_DIR}/triangles.cpp)

add_proj_test(line_tests ${TESTS_DIR}/line_tests.cpp)
add_proj_test(point_tests ${TESTS_DIR}/point_tests.cpp)
add_proj_test(vector_tests ${TESTS_DIR}/vector_tests.cpp)
add_proj_test(plane_tests ${TESTS_DIR}/plane_tests.cpp)
add_proj_test(triangles_tests ${TESTS_DIR}/triangles_tests.cpp)
