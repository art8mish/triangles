    
#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>
#include <vector.hpp>
#include <line.hpp>
#include <utils.hpp>

using triangles::zero;
using triangles::equal;
using triangles::nan;

class TestLine : public ::testing::Test
{
protected:
    using point_t = typename triangles::Point<double>;
    using vec_t = typename triangles::Vector<double>;
    using plane_t = typename triangles::Plane<double>;
    using line_t = typename triangles::Line<double>;

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestLine, InitZero) {
    point_t p_zero1 {};
    point_t p_zero2 {};
    line_t line_def_zero1 {p_zero1, p_zero2};
    ASSERT_EQ(false, line_def_zero1.is_valid());
    ASSERT_EQ(true, line_def_zero1.point().is_valid());
    ASSERT_EQ(true, line_def_zero1.point().is_zero());
    ASSERT_EQ(true, line_def_zero1.direction().is_valid());
    ASSERT_EQ(true, line_def_zero1.direction().is_zero());

    vec_t vec_zero {};
    line_t line_def_zero2 {p_zero1, vec_zero};
    ASSERT_EQ(false, line_def_zero2.is_valid());
    ASSERT_EQ(true, line_def_zero2.point().is_valid());
    ASSERT_EQ(true, line_def_zero2.point().is_zero());
    ASSERT_EQ(true, line_def_zero2.direction().is_valid());
    ASSERT_EQ(true, line_def_zero2.direction().is_zero());

    line_t line_def_zero3 {0, 0, 0, 0, 0, 0};
    ASSERT_EQ(false, line_def_zero3.is_valid());
    ASSERT_EQ(true, line_def_zero3.point().is_valid());
    ASSERT_EQ(true, line_def_zero3.point().is_zero());
    ASSERT_EQ(true, line_def_zero3.direction().is_valid());
    ASSERT_EQ(true, line_def_zero3.direction().is_zero());

    line_t line_def_zero4 {4, 1, 3, 4, 1, 3};
    ASSERT_EQ(false, line_def_zero4.is_valid());
    ASSERT_EQ(true, line_def_zero4.point().is_valid());
    ASSERT_EQ(true, line_def_zero4.point().is_zero());
    ASSERT_EQ(true, line_def_zero4.direction().is_valid());
    ASSERT_EQ(true, line_def_zero4.direction().is_zero());

    point_t p_zero_same {4, 1, 3};
    line_t line_def_zero5 {p_zero_same, p_zero_same};
    ASSERT_EQ(false, line_def_zero5.is_valid());
    ASSERT_EQ(true, line_def_zero5.point().is_valid());
    ASSERT_EQ(true, line_def_zero5.point().is_zero());
    ASSERT_EQ(true, line_def_zero5.direction().is_valid());
    ASSERT_EQ(true, line_def_zero5.direction().is_zero());
}

TEST_F(TestLine, InitValid) {
    line_t line1 {4, 2, 3, 5, 0, 6};
    ASSERT_EQ(true, line1.is_valid());
    ASSERT_EQ(true, line1.point().is_valid());
    ASSERT_EQ(false, line1.point().is_zero());
    ASSERT_EQ(true, line1.direction().is_valid());
    ASSERT_EQ(false, line1.direction().is_zero());

    vec_t dir1 {1, -2, 3};
    ASSERT_EQ(true, line1.direction().collinear_with(dir1));

    point_t p1 {8, 4, 6};
    point_t p2 {10, 0, 12};
    line_t line2 {p1, p2};
    ASSERT_EQ(true, line2.is_valid());
    ASSERT_EQ(true, line2.point().is_valid());
    ASSERT_EQ(false, line2.point().is_zero());
    ASSERT_EQ(true, line2.direction().is_valid());
    ASSERT_EQ(false, line2.direction().is_zero());
    ASSERT_EQ(true, line2.direction().collinear_with(dir1));

    
    line_t line3 {p1, dir1};
    ASSERT_EQ(true, line3.is_valid());
    ASSERT_EQ(true, line3.point().is_valid());
    ASSERT_EQ(false, line3.point().is_zero());
    ASSERT_EQ(true, line3.direction().is_valid());
    ASSERT_EQ(false, line3.direction().is_zero());
    ASSERT_EQ(true, line3.direction().collinear_with(dir1));
}

TEST_F(TestLine, InitPlane) {
    point_t p1 {4, 2, 3};
    point_t p2 {5, 0, 6};

    vec_t plane_n1 {-2, -1, 0};
    plane_t plane1 {p1, plane_n1};
    ASSERT_EQ(true, plane1.normal().collinear_with(plane_n1));

    vec_t plane_n2 {3, -6, -5};
    plane_t plane2 {p2, plane_n2};
    ASSERT_EQ(true, plane2.normal().collinear_with(plane_n2));

    line_t line1 {plane1, plane2};
    line_t line2 {p1, p2};
    ASSERT_EQ(true, line1 == line2);

    vec_t plane_n3 {4, 2, 0};
    plane_t plane3 {p2, plane_n3};
    ASSERT_EQ(true, plane3.normal().collinear_with(plane_n3));
    ASSERT_EQ(true, plane_n3.collinear_with(plane_n1));

    EXPECT_THROW((line_t {plane1, plane3}), std::logic_error);
}


TEST_F(TestLine, Equality) {
    line_t line1 {4, 2, 3, 5, 0, 6};
    line_t line2 {4, 2, 3, 5, 0, 6};
    ASSERT_EQ(true, line1 == line2);
    ASSERT_EQ(false, line1 != line2);

    ASSERT_EQ(true, (line1 == line2) == (line2 == line1));
    ASSERT_EQ(true, (line1 != line2) == (line2 != line1));

    ASSERT_EQ(true, line1.direction().collinear_with(line2.direction()));
    
    point_t p1 {8, -6, 15};
    point_t p2 {6, -2, 9};
    line_t line3 {p1, p2};
    ASSERT_EQ(true, line1 == line3);
    ASSERT_EQ(false, line1 != line3);
    ASSERT_EQ(true, (line1 == line3) == (line3 == line1));
    ASSERT_EQ(true, (line1 != line3) == (line3 != line1));
    ASSERT_EQ(true, line1.direction().collinear_with(line3.direction()));

    line_t line4 {p2, p1};
    ASSERT_EQ(true, line1 == line4);
    ASSERT_EQ(false, line1 != line4);
    ASSERT_EQ(true, (line1 == line4) == (line4 == line1));
    ASSERT_EQ(true, (line1 != line4) == (line4 != line1));
    ASSERT_EQ(true, line1.direction().collinear_with(line4.direction()));

    vec_t dir1 {1, -2, 3};
    line_t line5 {p1, dir1};
    ASSERT_EQ(true, line1 == line5);
    ASSERT_EQ(false, line1 != line5);
    ASSERT_EQ(true, (line1 == line5) == (line5 == line1));
    ASSERT_EQ(true, (line1 != line5) == (line5 != line1));
    ASSERT_EQ(true, line1.direction().collinear_with(line5.direction()));

    line_t line_non_eq {4, 2, 0, 5, 0, 6};
    ASSERT_EQ(false, line_non_eq == line1);
    ASSERT_EQ(true, line_non_eq != line1);
    ASSERT_EQ(true, (line_non_eq == line1) == (line1 == line_non_eq));
    ASSERT_EQ(true, (line_non_eq != line1) == (line1 != line_non_eq));
    ASSERT_EQ(false, line_non_eq.direction().collinear_with(line1.direction()));

    ASSERT_EQ(false, line_non_eq == line3);
    ASSERT_EQ(true, line_non_eq != line3);
    ASSERT_EQ(true, (line_non_eq == line3) == (line3 == line_non_eq));
    ASSERT_EQ(true, (line_non_eq != line3) == (line3 != line_non_eq));
    ASSERT_EQ(false, line_non_eq.direction().collinear_with(line3.direction()));

    ASSERT_EQ(false, line_non_eq == line4);
    ASSERT_EQ(true, line_non_eq != line4);
    ASSERT_EQ(true, (line_non_eq == line4) == (line4 == line_non_eq));
    ASSERT_EQ(true, (line_non_eq != line4) == (line4 != line_non_eq));
    ASSERT_EQ(false, line_non_eq.direction().collinear_with(line4.direction()));

    ASSERT_EQ(false, line_non_eq == line5);
    ASSERT_EQ(true, line_non_eq != line5);
    ASSERT_EQ(true, (line_non_eq == line5) == (line5 == line_non_eq));
    ASSERT_EQ(true, (line_non_eq != line5) == (line5 != line_non_eq));
    ASSERT_EQ(false, line_non_eq.direction().collinear_with(line5.direction()));

    line_t line_invalid {4, 2, 3, 5, 0, nan<double>()};
    ASSERT_EQ(false, line_invalid.is_valid());
    EXPECT_THROW(line_invalid == line1, std::logic_error);
    EXPECT_THROW(line1 == line_invalid, std::logic_error);
    EXPECT_THROW(line_invalid != line1, std::logic_error);
    EXPECT_THROW(line1 != line_invalid, std::logic_error);
}

TEST_F(TestLine, Contains) {
    point_t p1 {4, 2, 3};
    point_t p2 {5, 0, 6};
    line_t line {p1, p2};
    ASSERT_EQ(true, line.contains(p1));
    ASSERT_EQ(true, line.contains(p2));
    ASSERT_EQ(true, line.contains(point_t {9, -8, 18}));
    ASSERT_EQ(true, line.contains(point_t {1, 8, -6}));

    ASSERT_EQ(false, line.contains(point_t {0, 0, 0}));
    ASSERT_EQ(false, line.contains(point_t {4, 3, 4}));

    line_t line_invalid {p1, vec_t {0, 0, 0}};
    ASSERT_EQ(false, line_invalid.is_valid());
    EXPECT_THROW(line_invalid.contains(p1), std::logic_error);
}


TEST_F(TestLine, ParallelLines) {
    point_t p1 {4, 2, 3};
    point_t p2 {5, 0, 6};

    line_t line1 {p1, p2};
    ASSERT_EQ(true, line1.parallel_to(line1));

    point_t p3 {8, 14, 4};
    point_t p4 {10, 10, 10};

    line_t line2 {p3, p4};
    ASSERT_EQ(true, line2.parallel_to(line1));
    ASSERT_EQ(true, line1.parallel_to(line2));

    line_t line3 {p1, p4};
    ASSERT_EQ(false, line3.parallel_to(line1));
    ASSERT_EQ(false, line1.parallel_to(line3));
    ASSERT_EQ(false, line3.parallel_to(line2));
    ASSERT_EQ(false, line2.parallel_to(line3));


    line_t line_invalid {p1, p1};
    ASSERT_EQ(false, line_invalid.is_valid());
    EXPECT_THROW(line_invalid.parallel_to(line1), std::logic_error);
    EXPECT_THROW(line1.parallel_to(line_invalid), std::logic_error);
}