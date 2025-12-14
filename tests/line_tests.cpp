
#include <fstream>
#include <stdexcept>
#include <gtest/gtest.h>

#include "line.hpp"
#include "point.hpp"
#include "utils.hpp"
#include "vector.hpp"

using triangles::nan;

class TestLine : public ::testing::Test {
protected:
    using point_t = typename triangles::Point<double>;
    using vec_t = typename triangles::Vector<double>;
    using plane_t = typename triangles::Plane<double>;
    using line_t = typename triangles::Line<double>;

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestLine, InitZero) {
    point_t p_zero1{};
    point_t p_zero2{};
    ASSERT_THROW((line_t {p_zero1, p_zero2}), std::logic_error);

    vec_t vec_zero{};
    ASSERT_THROW((line_t {p_zero1, vec_zero}), std::logic_error);


    ASSERT_THROW((line_t {0, 0, 0, 0, 0, 0}), std::logic_error);
    ASSERT_THROW((line_t {4, 1, 3, 4, 1, 3}), std::logic_error);

    point_t p_zero_same{4, 1, 3};
    ASSERT_THROW((line_t {p_zero_same, p_zero_same}), std::logic_error);
}

TEST_F(TestLine, InitValid) {
    line_t line1{4, 2, 3, 5, 0, 6};
    ASSERT_FALSE(line1.point().is_zero());
    ASSERT_FALSE(line1.direction().is_zero());

    vec_t dir1{1, -2, 3};
    ASSERT_TRUE(line1.direction().collinear_with(dir1));

    point_t p1{8, 4, 6};
    point_t p2{10, 0, 12};
    line_t line2{p1, p2};
    ASSERT_FALSE(line2.point().is_zero());
    ASSERT_FALSE(line2.direction().is_zero());
    ASSERT_TRUE(line2.direction().collinear_with(dir1));

    line_t line3{p1, dir1};
    ASSERT_FALSE(line3.point().is_zero());
    ASSERT_FALSE(line3.direction().is_zero());
    ASSERT_TRUE(line3.direction().collinear_with(dir1));
}

TEST_F(TestLine, InitPlane) {
    point_t p1{4, 2, 3};
    point_t p2{5, 0, 6};

    vec_t plane_n1{-2, -1, 0};
    plane_t plane1{p1, plane_n1};
    ASSERT_TRUE(plane1.normal().collinear_with(plane_n1));

    vec_t plane_n2{3, -6, -5};
    plane_t plane2{p2, plane_n2};
    ASSERT_TRUE(plane2.normal().collinear_with(plane_n2));

    line_t line1{plane1, plane2};
    line_t line2{p1, p2};
    ASSERT_TRUE(line1 == line2);

    vec_t plane_n3{4, 2, 0};
    plane_t plane3{p2, plane_n3};
    ASSERT_TRUE(plane3.normal().collinear_with(plane_n3));
    ASSERT_TRUE(plane_n3.collinear_with(plane_n1));

    ASSERT_THROW((line_t{plane1, plane3}), std::logic_error);
}

TEST_F(TestLine, Equality) {
    line_t line1{4, 2, 3, 5, 0, 6};
    line_t line2{4, 2, 3, 5, 0, 6};
    ASSERT_TRUE(line1 == line2);
    ASSERT_FALSE(line1 != line2);

    ASSERT_TRUE((line1 == line2) == (line2 == line1));
    ASSERT_TRUE((line1 != line2) == (line2 != line1));

    ASSERT_TRUE(line1.direction().collinear_with(line2.direction()));

    point_t p1{8, -6, 15};
    point_t p2{6, -2, 9};
    line_t line3{p1, p2};
    ASSERT_TRUE(line1 == line3);
    ASSERT_FALSE(line1 != line3);
    ASSERT_TRUE((line1 == line3) == (line3 == line1));
    ASSERT_TRUE((line1 != line3) == (line3 != line1));
    ASSERT_TRUE(line1.direction().collinear_with(line3.direction()));

    line_t line4{p2, p1};
    ASSERT_TRUE(line1 == line4);
    ASSERT_FALSE(line1 != line4);
    ASSERT_TRUE((line1 == line4) == (line4 == line1));
    ASSERT_TRUE((line1 != line4) == (line4 != line1));
    ASSERT_TRUE(line1.direction().collinear_with(line4.direction()));

    vec_t dir1{1, -2, 3};
    line_t line5{p1, dir1};
    ASSERT_TRUE(line1 == line5);
    ASSERT_FALSE(line1 != line5);
    ASSERT_TRUE((line1 == line5) == (line5 == line1));
    ASSERT_TRUE((line1 != line5) == (line5 != line1));
    ASSERT_TRUE(line1.direction().collinear_with(line5.direction()));

    line_t line_non_eq{4, 2, 0, 5, 0, 6};
    ASSERT_FALSE(line_non_eq == line1);
    ASSERT_TRUE(line_non_eq != line1);
    ASSERT_TRUE((line_non_eq == line1) == (line1 == line_non_eq));
    ASSERT_TRUE((line_non_eq != line1) == (line1 != line_non_eq));
    ASSERT_FALSE(line_non_eq.direction().collinear_with(line1.direction()));

    ASSERT_FALSE(line_non_eq == line3);
    ASSERT_TRUE(line_non_eq != line3);
    ASSERT_TRUE((line_non_eq == line3) == (line3 == line_non_eq));
    ASSERT_TRUE((line_non_eq != line3) == (line3 != line_non_eq));
    ASSERT_FALSE(line_non_eq.direction().collinear_with(line3.direction()));

    ASSERT_FALSE(line_non_eq == line4);
    ASSERT_TRUE(line_non_eq != line4);
    ASSERT_TRUE((line_non_eq == line4) == (line4 == line_non_eq));
    ASSERT_TRUE((line_non_eq != line4) == (line4 != line_non_eq));
    ASSERT_FALSE(line_non_eq.direction().collinear_with(line4.direction()));

    ASSERT_FALSE(line_non_eq == line5);
    ASSERT_TRUE(line_non_eq != line5);
    ASSERT_TRUE((line_non_eq == line5) == (line5 == line_non_eq));
    ASSERT_TRUE((line_non_eq != line5) == (line5 != line_non_eq));
    ASSERT_FALSE(line_non_eq.direction().collinear_with(line5.direction()));

    ASSERT_THROW((line_t {4, 2, 3, 5, 0, nan<double>()}), std::logic_error);
}

TEST_F(TestLine, Contains) {
    point_t p1{4, 2, 3};
    point_t p2{5, 0, 6};
    line_t line{p1, p2};
    ASSERT_TRUE(line.contains(p1));
    ASSERT_TRUE(line.contains(p2));
    ASSERT_TRUE(line.contains(point_t{9, -8, 18}));
    ASSERT_TRUE(line.contains(point_t{1, 8, -6}));

    ASSERT_FALSE(line.contains(point_t{0, 0, 0}));
    ASSERT_FALSE(line.contains(point_t{4, 3, 4}));

    ASSERT_THROW((line_t {p1, vec_t{0, 0, 0}}), std::logic_error);
}

TEST_F(TestLine, ParallelLines) {
    point_t p1{4, 2, 3};
    point_t p2{5, 0, 6};

    line_t line1{p1, p2};
    ASSERT_TRUE(line1.parallel_to(line1));

    point_t p3{8, 14, 4};
    point_t p4{10, 10, 10};

    line_t line2{p3, p4};
    ASSERT_TRUE(line2.parallel_to(line1));
    ASSERT_TRUE(line1.parallel_to(line2));

    line_t line3{p1, p4};
    ASSERT_FALSE(line3.parallel_to(line1));
    ASSERT_FALSE(line1.parallel_to(line3));
    ASSERT_FALSE(line3.parallel_to(line2));
    ASSERT_FALSE(line2.parallel_to(line3));


    ASSERT_THROW((line_t {p1, p1}), std::logic_error);
}

TEST_F(TestLine, PlaneIntersectionPoint) {
    point_t p1{1, 2, 3};
    point_t p2{2, 4, 5};
    point_t p3{1, 4, 1};

    plane_t plane1{p1, p2, p3};
    
    point_t p1_perp2{-3, 3, 4};
    line_t line_perpendicular {p1, p1_perp2};
    ASSERT_TRUE(line_perpendicular.intersection_point(plane1) == p1);

    line_t line_paral{p1, p2};
    ASSERT_THROW(line_paral.intersection_point(plane1), std::invalid_argument);

    point_t p2_perp2{-2, 5, 6};
    line_t line_seq{p2_perp2, p1};
    ASSERT_TRUE(line_seq.intersection_point(plane1) == p1);

    point_t p1_perp1{-1, 2.5, 3.5};
    point_t p1_p2_perp2_mid{-0.5, 3.5, 4.5};
    point_t p3_perp1{-1, 4.5, 1.5};
    plane_t plane2{p1_perp1, p1_p2_perp2_mid, p3_perp1};

    // std::cout << "Intersec point: " +
    // tr_t::plane_line_intersection_point(plane2, line_seq).to_string() + '\n';
    ASSERT_TRUE(line_seq.intersection_point(plane2) == p1_p2_perp2_mid);
    ASSERT_THROW(line_paral.intersection_point(plane2), std::invalid_argument);
}