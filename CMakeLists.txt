cmake_minimum_required(VERSION 3.28.3)

set(TARGET triangles)
project(${TARGET})

set(SRC_DIR src)
set(INCLUDE_DIR include)

set(SRC ${SRC_DIR}/triangles.cpp)


set(TESTS_DIR tests)

set(TESTS_TARGET triangles_tests)
set(TESTS_SRC ${TESTS_DIR}/triangles_tests.cpp)

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

add_executable(${TESTS_TARGET} ${TESTS_SRC})
target_link_libraries(${TESTS_TARGET} gtest gmock pthread)