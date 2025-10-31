#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>
#include <triangles.hpp>
#include <utils.hpp>

class TestTriangles : public ::testing::Test
{
protected:

    using point_t = typename triangles::Point<double>;
    // vec_t = typename triangles::Vector<double>;
    using tr_t = typename triangles::Triangle<double>;
    
    void SetUp() {}
    void TearDown() {}
};


TEST_F(TestTriangles, InitInvalid) {
    point_t p_zero1 {};
    point_t p_zero2 {};
    line_t line_def_zero1 {p_zero1, p_zero2};
    ASSERT_EQ(false, line_def_zero1.is_valid());
    ASSERT_THROW(line_def_zero1.point(), std::logic_error);
    ASSERT_THROW(line_def_zero1.direction(), std::logic_error);

    vec_t vec_zero {};
    line_t line_def_zero2 {p_zero1, vec_zero};
    ASSERT_EQ(false, line_def_zero2.is_valid());
    ASSERT_THROW(line_def_zero2.point(), std::logic_error);
    ASSERT_THROW(line_def_zero2.direction(), std::logic_error);

    line_t line_def_zero3 {0, 0, 0, 0, 0, 0};
    ASSERT_EQ(false, line_def_zero3.is_valid());
    ASSERT_THROW(line_def_zero3.point(), std::logic_error);
    ASSERT_THROW(line_def_zero3.direction(), std::logic_error);

    line_t line_def_zero4 {4, 1, 3, 4, 1, 3};
    ASSERT_EQ(false, line_def_zero4.is_valid());
    ASSERT_THROW(line_def_zero4.point(), std::logic_error);
    ASSERT_THROW(line_def_zero4.direction(), std::logic_error);

    point_t p_zero_same {4, 1, 3};
    line_t line_def_zero5 {p_zero_same, p_zero_same};
    ASSERT_EQ(false, line_def_zero5.is_valid());
    ASSERT_THROW(line_def_zero5.point(), std::logic_error);
    ASSERT_THROW(line_def_zero5.direction(), std::logic_error);
}