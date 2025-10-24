    
#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>
#include <vector.hpp>
#include <line.hpp>
#include <utils.hpp>

using triangles::zero;
using triangles::equal;
using triangles::nan;

class TestPlane : public ::testing::Test
{
protected:
    using point_t = typename triangles::Point<double>;
    using vec_t = typename triangles::Vector<double>;
    using plane_t = typename triangles::Plane<double>;
    double eps_ = triangles::epsilon<double>();

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestPlane, InitInvalid) {
    point_t p_zero1 {};
    point_t p_zero2 {};
    point_t p_zero3 {};
    plane_t plane_def_zero1 {p_zero1, p_zero2, p_zero3};
    ASSERT_EQ(false, plane_def_zero1.is_valid());
    ASSERT_EQ(true, plane_def_zero1.normal().is_valid());
    ASSERT_EQ(true, plane_def_zero1.normal().is_zero());

    point_t p_valid1 {1, 2, 3};
    vec_t vec_zero {};
    plane_t plane_def_zero2 {p_valid1, vec_zero};
    ASSERT_EQ(false, plane_def_zero2.is_valid());
    ASSERT_EQ(true, plane_def_zero2.normal().is_valid());
    ASSERT_EQ(true, plane_def_zero2.normal().is_zero());

    plane_t plane_def_zero3 {p_valid1, p_valid1, p_valid1};
    ASSERT_EQ(false, plane_def_zero3.is_valid());
    ASSERT_EQ(true, plane_def_zero3.normal().is_valid());
    ASSERT_EQ(true, plane_def_zero3.normal().is_zero());

    point_t p_valid2 {3, 4, 5};
    plane_t plane_def_zero4 {p_valid1, p_valid1, p_valid2};
    ASSERT_EQ(false, plane_def_zero4.is_valid());
    ASSERT_EQ(true, plane_def_zero4.normal().is_valid());
    ASSERT_EQ(true, plane_def_zero4.normal().is_zero());

    point_t p_valid3 {5, 6, 7}; // same line with p_valid1 and p_valid2
    plane_t plane_def_zero5 {p_valid1, p_valid1, p_valid3};
    ASSERT_EQ(false, plane_def_zero4.is_valid());
    ASSERT_EQ(true, plane_def_zero4.normal().is_valid());
    ASSERT_EQ(true, plane_def_zero4.normal().is_zero());

    point_t p_invalid {1, 2, nan<double>()};
    vec_t vec_valid {1, 2, 3};
    plane_t plane_def_invalid {p_invalid, vec_valid};
    ASSERT_EQ(false, plane_def_invalid.is_valid());
    ASSERT_EQ(true, plane_def_invalid.normal().is_valid());
    ASSERT_EQ(false, plane_def_invalid.normal().is_zero());

    ASSERT_THROW((plane_t {p_valid1, p_valid2, p_invalid}), std::logic_error);
}

TEST_F(TestPlane, InitValid) {
    point_t p_zero {};
    point_t p_valid1 {1, 0, 0};
    point_t p_valid2 {1, 0, 1};

    plane_t plane1 {p_zero, p_valid1, p_valid2};
    ASSERT_EQ(true, plane1.is_valid());
    ASSERT_EQ(true, plane1.normal().is_valid());
    ASSERT_EQ(false, plane1.normal().is_zero());
    ASSERT_EQ(true, plane1.normal().collinear_with(vec_t {0, 1, 0}));

    vec_t vec_valid {1, 2, 3};
    plane_t plane2 {p_zero, vec_valid};
    ASSERT_EQ(true, plane2.is_valid());
    ASSERT_EQ(true, plane2.normal().is_valid());
    ASSERT_EQ(false, plane2.normal().is_zero());
    ASSERT_EQ(true, plane2.normal().collinear_with(vec_valid));
}

TEST_F(TestPlane, Equality) {
    point_t p_zero {};
    point_t p_valid1 {1, 0, 0};
    point_t p_valid2 {1, 0, 1};

    plane_t plane_main {p_zero, p_valid1, p_valid2};
    ASSERT_EQ(true, plane_main == plane_main);

    plane_t plane_same {p_zero, p_valid1, p_valid2};
    ASSERT_EQ(true, plane_main == plane_same);
    ASSERT_EQ(false, plane_main != plane_same);
    ASSERT_EQ(true, (plane_main == plane_same) == (plane_same == plane_main));
    ASSERT_EQ(true, (plane_main != plane_same) == (plane_same != plane_main));
    ASSERT_EQ(true, plane_main.normal().collinear_with(plane_same.normal()));

    vec_t vec_eq {0, 1, 0};
    plane_t plane_eq {p_zero, vec_eq};
    ASSERT_EQ(true, plane_main == plane_eq);
    ASSERT_EQ(false, plane_main != plane_eq);
    ASSERT_EQ(true, (plane_main == plane_eq) == (plane_eq == plane_main));
    ASSERT_EQ(true, (plane_main != plane_eq) == (plane_eq != plane_main));
    ASSERT_EQ(true, plane_main.normal().collinear_with(plane_eq.normal()));

    point_t p_valid3 {1, 1, 1};
    plane_t plane_non_eq {p_zero, p_valid1, p_valid3};
    ASSERT_EQ(false, plane_main == plane_non_eq);
    ASSERT_EQ(true, plane_main != plane_non_eq);
    ASSERT_EQ(true, (plane_main == plane_non_eq) == (plane_non_eq == plane_main));
    ASSERT_EQ(true, (plane_main != plane_non_eq) == (plane_non_eq != plane_main));
    ASSERT_EQ(false, plane_main.normal().collinear_with(plane_non_eq.normal()));

    ASSERT_EQ(false, plane_eq == plane_non_eq);
    ASSERT_EQ(true, plane_eq != plane_non_eq);
    ASSERT_EQ(true, (plane_eq == plane_non_eq) == (plane_non_eq == plane_eq));
    ASSERT_EQ(true, (plane_eq != plane_non_eq) == (plane_non_eq != plane_eq));
    ASSERT_EQ(false, plane_eq.normal().collinear_with(plane_non_eq.normal()));

    point_t p_invalid {1, 2, nan<double>()};
    plane_t plane_invalid {p_invalid, vec_eq};
    ASSERT_EQ(false, plane_invalid.is_valid());
    ASSERT_THROW(plane_main == plane_invalid, std::logic_error);
    ASSERT_THROW(plane_invalid == plane_main, std::logic_error);
    ASSERT_THROW(plane_main != plane_invalid, std::logic_error);
    ASSERT_THROW(plane_invalid != plane_main, std::logic_error);
}

TEST_F(TestPlane, Contains) {
    point_t p_zero {};
    point_t p1 {1, 0, 0};
    point_t p2 {1, 0, 1};
    plane_t plane {p_zero, p1, p2};
    ASSERT_EQ(true, plane.contains(p_zero));
    ASSERT_EQ(true, plane.contains(p1));
    ASSERT_EQ(true, plane.contains(p2));

    ASSERT_EQ(true, plane.contains(point_t {0, 0, 10}));
    ASSERT_EQ(true, plane.contains(point_t {5, 0, -5}));

    ASSERT_EQ(false, plane.contains(point_t {0, 1, 0}));
    ASSERT_EQ(false, plane.contains(point_t {4, 3, 4}));

    vec_t vec_zero {};
    plane_t plane_invalid {p_zero, vec_zero};
    ASSERT_EQ(false, plane_invalid.is_valid());
    ASSERT_THROW(plane_invalid.contains(p_zero), std::logic_error);
}

TEST_F(TestPlane, ParallelPlanes) {
    point_t p_zero {};
    point_t p1 {1, 0, 0};
    plane_t plane1 {p_zero, p1, point_t{1, 0, 1}};
    ASSERT_EQ(true, plane1.parallel_to(plane1));
    ASSERT_EQ(true, plane1.normal().collinear_with(plane1.normal()));

    plane_t plane2 {point_t{0, 2, 0}, point_t{1, 2, 0}, point_t{1, 2, 1}};
    ASSERT_EQ(true, plane1.parallel_to(plane2));
    ASSERT_EQ(true, plane2.parallel_to(plane1));
    ASSERT_EQ(true, plane1.normal().collinear_with(plane2.normal()));


    plane_t plane3 {p_zero, p1, point_t{1, 1, 1}};
    ASSERT_EQ(false, plane3.parallel_to(plane1));
    ASSERT_EQ(false, plane1.parallel_to(plane3));
    ASSERT_EQ(false, plane3.normal().collinear_with(plane1.normal()));

    ASSERT_EQ(false, plane3.parallel_to(plane2));
    ASSERT_EQ(false, plane2.parallel_to(plane3));
    ASSERT_EQ(false, plane3.normal().collinear_with(plane2.normal()));

    plane_t plane_invalid {p_zero, p1, point_t{2, 0, 0}};
    ASSERT_EQ(false, plane_invalid.is_valid());

    ASSERT_THROW(plane_invalid.parallel_to(plane1), std::logic_error);
    ASSERT_THROW(plane1.parallel_to(plane_invalid), std::logic_error);
}

TEST_F(TestPlane, SignedDistance) {
    point_t p_zero {};
    point_t p1 {1, 0, 0};
    point_t p2 {1, 0, 1};
    plane_t plane {p_zero, p1, p2};
    ASSERT_EQ(true, zero<double>(plane.signed_distance(p_zero), eps_));
    ASSERT_EQ(true, zero<double>(plane.signed_distance(p1), eps_));
    ASSERT_EQ(true, zero<double>(plane.signed_distance(p2), eps_));

    ASSERT_EQ(true, zero<double>(plane.signed_distance(point_t {5, 0, 10}), eps_));
    
    double dist1 = plane.signed_distance(point_t {1, 2, 1});
    double dist2 = plane.signed_distance(point_t {1, -2, 1});
    ASSERT_EQ(true, equal<double>(std::abs(dist1), 2, eps_));
    ASSERT_EQ(true, equal<double>(std::abs(dist2), 2, eps_));
    ASSERT_EQ(true, equal<double>(dist1 * dist2, -4, eps_));

    double dist3 = plane.signed_distance(point_t {1, -4, 1});
    ASSERT_EQ(true, equal<double>(std::abs(dist3), 4, eps_));
    ASSERT_EQ(true, equal<double>(dist3 * dist2, 8, eps_));

    ASSERT_THROW(plane.signed_distance(point_t {1, -4, nan<double>()}), std::logic_error);

    plane_t plane_invalid {p_zero, p1, point_t{2, 0, 0}};
    ASSERT_EQ(false, plane_invalid.is_valid());
    ASSERT_THROW(plane_invalid.signed_distance(p1), std::logic_error);
}

TEST_F(TestPlane, DCoefficient) {
    point_t p1 {2, 0, 0};
    point_t p2 {0, 2, 0};
    point_t p3 {1, 1, 1};
    plane_t plane {p1, p2, p3};

    point_t p4 {1, 1, 5};
    ASSERT_EQ(true, plane.contains(p4));
    ASSERT_EQ(true, zero<double>(plane.normal().edot(vec_t {p4}) + plane.D(), eps_));

    plane_t plane_invalid {p1, vec_t {1, 2, nan<double>()}};
    ASSERT_EQ(false, plane_invalid.is_valid());
    ASSERT_THROW(plane_invalid.D(), std::logic_error);
}