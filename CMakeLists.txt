cmake_minimum_required(VERSION 3.28.3)

set(TARGET triangles)
project(${TARGET})

set(SRC_DIR src)
set(INCLUDE_DIR include)

set(SRC ${SRC_DIR}/triangles.cpp)


set(TESTS_DIR tests)

set(TEST_POINT point_tests)
set(TEST_POINT_SRC ${TESTS_DIR}/point_tests.cpp)

set(TEST_VECTOR vector_tests)
set(TEST_VECTOR_SRC ${TESTS_DIR}/vector_tests.cpp)

set(TEST_LINE line_tests)
set(TEST_LINE_SRC ${TESTS_DIR}/line_tests.cpp)

add_compile_options(
    -D DEBUG
    -g
    
    -std=c++20

    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

include_directories(${INCLUDE_DIR})
add_executable(${TARGET} ${SRC})

add_executable(${TEST_POINT} ${TEST_POINT_SRC})
target_link_libraries(${TEST_POINT} gtest gmock pthread)

add_executable(${TEST_VECTOR} ${TEST_VECTOR_SRC})
target_link_libraries(${TEST_VECTOR} gtest gmock pthread)

add_executable(${TEST_LINE} ${TEST_LINE_SRC})
target_link_libraries(${TEST_LINE} gtest gmock pthread)