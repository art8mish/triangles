
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "point.hpp"
#include "utils.hpp"
#include "vector.hpp"

using triangles::equal;
using triangles::nan;
using triangles::zero;

class TestVector : public ::testing::Test {
protected:
    using vec_t = typename triangles::Vector<double>;
    using point_t = typename triangles::Point<double>;
    double eps_ = triangles::epsilon<double>();

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestVector, Init) {
    vec_t vec_def_zero1{};
    ASSERT_TRUE(vec_def_zero1.is_valid());
    ASSERT_TRUE(vec_def_zero1.is_zero());

    vec_t vec_delta{16.2, 7.56, 0.0};
    ASSERT_TRUE(vec_delta.is_valid());
    ASSERT_FALSE(vec_delta.is_zero());

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points{p_from, p_to};
    ASSERT_TRUE(vec_points.is_valid());
    ASSERT_FALSE(vec_points.is_zero());

    vec_t vec_nums{0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_TRUE(vec_nums.is_valid());
    ASSERT_FALSE(vec_nums.is_zero());
}

TEST_F(TestVector, IsZero) {
    vec_t vec_def_zero1{};
    ASSERT_TRUE(vec_def_zero1.is_valid());
    ASSERT_TRUE(vec_def_zero1.is_zero());

    vec_t vec_zero_delta{0.0, 0.0, 0.0};
    ASSERT_TRUE(vec_zero_delta.is_valid());
    ASSERT_TRUE(vec_zero_delta.is_zero());

    point_t p_zero_from = {0.0, 0.0, 0.0};
    point_t p_zero_to = {-0.0, 0.0, 0};
    vec_t vec_zero_points{p_zero_from, p_zero_to};
    ASSERT_TRUE(vec_zero_points.is_valid());
    ASSERT_TRUE(vec_zero_points.is_zero());

    vec_t vec_zero_nums{0.0, 0.0, 0, 0.0, 0, 0};
    ASSERT_TRUE(vec_zero_nums.is_valid());
    ASSERT_TRUE(vec_zero_nums.is_zero());

    vec_t vec_not_zero{0.01, 0.0, 0.0};
    ASSERT_TRUE(vec_not_zero.is_valid());
    ASSERT_FALSE(vec_not_zero.is_zero());
}

TEST_F(TestVector, LowDimensions) {
    vec_t vec_2d_1{16.2, 7.56};
    ASSERT_TRUE(vec_2d_1.is_valid());
    ASSERT_FALSE(vec_2d_1.is_zero());

    vec_t vec_2d_2{16.2, 7.56, 0.0};
    ASSERT_TRUE(vec_2d_2.is_valid());
    ASSERT_FALSE(vec_2d_2.is_zero());

    ASSERT_TRUE(vec_2d_1 == vec_2d_2);

    vec_t vec_1d_1{0.001};
    ASSERT_TRUE(vec_1d_1.is_valid());
    ASSERT_FALSE(vec_1d_1.is_zero());

    vec_t vec_1d_2{0.001, 0.0};
    ASSERT_TRUE(vec_1d_2.is_valid());
    ASSERT_FALSE(vec_1d_2.is_zero());

    vec_t vec_1d_3{0.001, 0.0, 0.0};
    ASSERT_TRUE(vec_1d_3.is_valid());
    ASSERT_FALSE(vec_1d_3.is_zero());

    ASSERT_TRUE(vec_1d_1 == vec_1d_2);
    ASSERT_TRUE(vec_1d_2 == vec_1d_3);
}

TEST_F(TestVector, Equality) {
    vec_t vec_zero{0.0, 0.0, 0.0};
    ASSERT_TRUE(vec_zero == vec_zero);

    vec_t vec_zero_eq{0.0, 0.0, 0.0};
    ASSERT_TRUE(vec_zero == vec_zero_eq);
    ASSERT_FALSE(vec_zero != vec_zero_eq);

    vec_t vec_zero_neq{0.0, 0.0, 0.01};
    ASSERT_FALSE(vec_zero == vec_zero_neq);
    ASSERT_TRUE(vec_zero != vec_zero_neq);

    vec_t vec_delta{16.2, 7.56, 0.0};
    ASSERT_TRUE(vec_delta == vec_delta);

    vec_t vec_delta_eq{16.2, 7.56, 0.0};
    ASSERT_TRUE(vec_delta == vec_delta_eq);
    ASSERT_FALSE(vec_delta != vec_delta_eq);

    ASSERT_TRUE((vec_delta == vec_delta_eq) == (vec_delta_eq == vec_delta));
    ASSERT_TRUE((vec_delta != vec_delta_eq) == (vec_delta_eq != vec_delta));

    vec_t vec_delta_neq{-16.2, 7.56, 0.0};
    ASSERT_FALSE(vec_delta == vec_delta_neq);
    ASSERT_TRUE(vec_delta != vec_delta_neq);

    ASSERT_TRUE((vec_delta == vec_delta_neq) == (vec_delta_neq == vec_delta));
    ASSERT_TRUE((vec_delta != vec_delta_neq) == (vec_delta_neq != vec_delta));

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points{p_from, p_to};
    vec_t vec_points_eq{p_from, p_to};
    ASSERT_TRUE(vec_points == vec_points_eq);
    ASSERT_FALSE(vec_points != vec_points_eq);

    ASSERT_TRUE((vec_points == vec_points_eq) == (vec_points_eq == vec_points));
    ASSERT_TRUE((vec_points != vec_points_eq) == (vec_points_eq != vec_points));

    point_t p_to_neq = {16.2, 7.56, -15.31};
    vec_t vec_points_neq_1{p_from, p_to_neq};
    ASSERT_FALSE(vec_points == vec_points_neq_1);
    ASSERT_TRUE(vec_points != vec_points_neq_1);

    ASSERT_TRUE((vec_points == vec_points_neq_1) ==
                (vec_points_neq_1 == vec_points));
    ASSERT_TRUE((vec_points != vec_points_neq_1) ==
                (vec_points_neq_1 != vec_points));

    point_t p_from_neq = {0.0, 0.001, 0.0};
    vec_t vec_points_neq_2{p_from_neq, p_to};
    ASSERT_FALSE(vec_points == vec_points_neq_2);
    ASSERT_TRUE(vec_points != vec_points_neq_2);

    ASSERT_TRUE((vec_points == vec_points_neq_2) ==
                (vec_points_neq_2 == vec_points));
    ASSERT_TRUE((vec_points != vec_points_neq_2) ==
                (vec_points_neq_2 != vec_points));

    vec_t vec_nums{0, 25.4, 6.7, 15.4, 94.3, 2.4};
    vec_t vec_nums_eq{0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_TRUE(vec_nums == vec_nums_eq);
    ASSERT_FALSE(vec_nums != vec_nums_eq);

    ASSERT_TRUE((vec_nums == vec_nums_eq) == (vec_nums_eq == vec_nums));
    ASSERT_TRUE((vec_nums != vec_nums_eq) == (vec_nums_eq != vec_nums));

    vec_t vec_nums_neq{0, 25.4, 6.8, 15.4, 94.3, 2.4};
    ASSERT_FALSE(vec_nums == vec_nums_neq);
    ASSERT_TRUE(vec_nums != vec_nums_neq);

    ASSERT_TRUE((vec_nums == vec_nums_neq) == (vec_nums_neq == vec_nums));
    ASSERT_TRUE((vec_nums != vec_nums_neq) == (vec_nums_neq != vec_nums));
}

TEST_F(TestVector, Enorm) {
    vec_t vec_zero{};
    ASSERT_TRUE(zero<double>(vec_zero.enorm(), eps_));

    vec_t vec_valid{1, -2, 3};
    ASSERT_TRUE(equal<double>(vec_valid.enorm(), std::sqrt(14), eps_));

    vec_t vec_invalid{1, 2, nan<double>()};
    ASSERT_FALSE(vec_invalid.is_valid());
    ASSERT_THROW(vec_invalid.enorm(), std::logic_error);
}

TEST_F(TestVector, Edot) {
    vec_t vec_zero1{};
    vec_t vec_zero2{};
    ASSERT_TRUE(zero<double>(vec_zero1.edot(vec_zero2), eps_));

    vec_t vec_main{1, -2, 3};
    ASSERT_TRUE(zero<double>(vec_main.edot(vec_zero1), eps_));
    ASSERT_TRUE(zero<double>(vec_zero1.edot(vec_main), eps_));

    vec_t vec1{1, 2, 1};
    ASSERT_TRUE(zero<double>(vec_main.edot(vec1), eps_));
    ASSERT_TRUE(zero<double>(vec1.edot(vec_main), eps_));

    vec_t vec2{3, 2, 1};
    ASSERT_TRUE(equal<double>(vec_main.edot(vec2), 2.0, eps_));
    ASSERT_TRUE(equal<double>(vec_main.edot(vec2), vec2.edot(vec_main), eps_));

    vec_t vec3{0, 0, 1};
    ASSERT_TRUE(equal<double>(vec_main.edot(vec3), 3.0, eps_));
    ASSERT_TRUE(equal<double>(vec_main.edot(vec3), vec3.edot(vec_main), eps_));
}

TEST_F(TestVector, Ecross) {
    vec_t vec_zero1{};
    vec_t vec_zero2{};
    ASSERT_TRUE(vec_zero1.ecross(vec_zero2).is_zero());

    vec_t vec_main{1, -2, 3};
    ASSERT_TRUE(vec_main.ecross(vec_zero1).is_zero());
    ASSERT_TRUE(vec_zero1.ecross(vec_main).is_zero());

    vec_t vec_col{2, -4, 6};
    ASSERT_TRUE(vec_main.ecross(vec_col).is_zero());
    ASSERT_TRUE(vec_col.ecross(vec_main).is_zero());

    vec_t vec2{5, 1, 2};
    ASSERT_TRUE((vec_main.ecross(vec2) == vec_t{-7, 13, 11}));
    ASSERT_TRUE((vec2.ecross(vec_main) == vec_t{7, -13, -11}));

    vec_t vec3{0, 0, 1};
    ASSERT_TRUE((vec_main.ecross(vec3) == vec_t{-2, -1, 0}));
    ASSERT_TRUE((vec3.ecross(vec_main) == vec_t{2, 1, 0}));
}

TEST_F(TestVector, Collinearity) {
    vec_t vec_zero1{};
    vec_t vec_zero2{};
    ASSERT_TRUE(vec_zero1.collinear_with(vec_zero2));
    ASSERT_TRUE(vec_zero2.collinear_with(vec_zero1));

    vec_t vec_main{2, 5, -3};
    ASSERT_TRUE(vec_main.collinear_with(vec_zero1));
    ASSERT_TRUE(vec_zero1.collinear_with(vec_main));

    vec_t vec_col1{6, 15, -9};
    ASSERT_TRUE(vec_main.collinear_with(vec_col1));
    ASSERT_TRUE(vec_col1.collinear_with(vec_main));

    vec_t vec_reverse1{-2, -5, 3};
    ASSERT_TRUE(vec_main.collinear_with(vec_reverse1));
    ASSERT_TRUE(vec_reverse1.collinear_with(vec_main));

    vec_t vec_reverse2{-4, -10, 6};
    ASSERT_TRUE(vec_main.collinear_with(vec_reverse2));
    ASSERT_TRUE(vec_reverse2.collinear_with(vec_main));

    vec_t vec_not_col{0, 5, 3};
    ASSERT_FALSE(vec_main.collinear_with(vec_not_col));
    ASSERT_FALSE(vec_not_col.collinear_with(vec_main));
}

TEST_F(TestVector, Orthogonality) {
    vec_t vec_zero1{};
    vec_t vec_zero2{};
    ASSERT_TRUE(vec_zero1.orthogonal_to(vec_zero2));
    ASSERT_TRUE(vec_zero2.orthogonal_to(vec_zero1));

    vec_t vec_main{2, 5, -3};
    ASSERT_TRUE(vec_main.orthogonal_to(vec_zero1));
    ASSERT_TRUE(vec_zero1.orthogonal_to(vec_main));

    vec_t vec_orthogonal{4, -1, 1};
    ASSERT_TRUE(vec_main.orthogonal_to(vec_orthogonal));
    ASSERT_TRUE(vec_orthogonal.orthogonal_to(vec_main));

    vec_t vec_not_orthogonal{-3, 2, 4};
    ASSERT_FALSE(vec_main.orthogonal_to(vec_not_orthogonal));
    ASSERT_FALSE(vec_not_orthogonal.orthogonal_to(vec_main));
}

TEST_F(TestVector, Normalization) {
    vec_t vec_normalized1{2.0 / 7, 3.0 / 7, 6.0 / 7};
    ASSERT_TRUE(vec_normalized1.is_normalized());
    vec_t vec_normalized2{0, 1, 0};
    ASSERT_TRUE(vec_normalized2.is_normalized());

    vec_t vec_invalid{1, 2, nan<double>()};
    ASSERT_FALSE(vec_invalid.is_valid());
    ASSERT_THROW(vec_invalid.is_normalized(), std::logic_error);

    vec_t vec_zero{};
    std::cout << vec_zero.to_string() << "\n";
    ASSERT_TRUE(vec_zero.is_zero());
    ASSERT_FALSE(vec_zero.is_normalized());

    vec_t vec_main{2, 6, -3};
    ASSERT_FALSE(vec_main.is_normalized());
    ASSERT_TRUE(equal<double>(vec_main.enorm(), 7, eps_));

    vec_main.normalize();
    ASSERT_TRUE(vec_main.collinear_with(vec_t{2, 6, -3}));
    ASSERT_TRUE(equal<double>(vec_main.edot(vec_main), 1, eps_));
    ASSERT_TRUE(equal<double>(vec_main.x(), 2.0 / 7, eps_));
    ASSERT_TRUE(equal<double>(vec_main.y(), 6.0 / 7, eps_));
    ASSERT_TRUE(equal<double>(vec_main.z(), -3.0 / 7, eps_));
    ASSERT_TRUE(vec_main.is_normalized());

    vec_t vec_rval = (vec_t{1, 2, 3}).normalize();
    ASSERT_TRUE(vec_rval.is_normalized());

    ASSERT_THROW(vec_invalid.normalize(), std::logic_error);
    ASSERT_NO_THROW(vec_zero.normalize());
}

TEST_F(TestVector, GetPerpendicular) {
    vec_t vec_zero{};
    ASSERT_TRUE(vec_zero.get_perpendicular().is_zero());

    vec_t vec1{2, 5, -3};
    vec_t vec_orth1 = vec1.get_perpendicular();
    ASSERT_TRUE(vec1.orthogonal_to(vec_orth1));
    ASSERT_TRUE(vec_orth1.orthogonal_to(vec1));

    vec_t vec2{0, 1, 2};
    vec_t vec_orth2 = vec2.get_perpendicular();
    ASSERT_TRUE(vec2.orthogonal_to(vec_orth2));
    ASSERT_TRUE(vec_orth2.orthogonal_to(vec2));

    vec_t vec3{0.001, 1, 0};
    vec_t vec_orth3 = vec3.get_perpendicular();
    ASSERT_TRUE(vec3.orthogonal_to(vec_orth3));
    ASSERT_TRUE(vec_orth3.orthogonal_to(vec3));

    vec_t vec4{0.001, 0.001, 0.001};
    vec_t vec_orth4 = vec4.get_perpendicular();
    ASSERT_TRUE(vec4.orthogonal_to(vec_orth4));
    ASSERT_TRUE(vec_orth4.orthogonal_to(vec4));
}

TEST_F(TestVector, InvalidStateExceptions) {
    vec_t vec_invalid{1, 2, nan<double>()};
    ASSERT_FALSE(vec_invalid.is_valid());

    ASSERT_THROW(vec_invalid.is_zero(), std::logic_error);

    ASSERT_THROW(vec_invalid.x(), std::logic_error);
    ASSERT_THROW(vec_invalid.y(), std::logic_error);
    ASSERT_THROW(vec_invalid.z(), std::logic_error);

    ASSERT_THROW(vec_invalid.normalize(), std::logic_error);
    ASSERT_THROW(vec_invalid.get_perpendicular(), std::logic_error);

    vec_t vec_valid{1, 2, 3};
    ASSERT_TRUE(vec_valid.is_valid());

    ASSERT_THROW(vec_valid == vec_invalid, std::logic_error);
    ASSERT_THROW(vec_invalid == vec_valid, std::logic_error);

    ASSERT_THROW(vec_valid != vec_invalid, std::logic_error);
    ASSERT_THROW(vec_invalid != vec_valid, std::logic_error);

    ASSERT_THROW(vec_valid.edot(vec_invalid), std::logic_error);
    ASSERT_THROW(vec_invalid.edot(vec_valid), std::logic_error);

    ASSERT_THROW(vec_valid.ecross(vec_invalid), std::logic_error);
    ASSERT_THROW(vec_invalid.ecross(vec_valid), std::logic_error);

    ASSERT_THROW(vec_valid.collinear_with(vec_invalid), std::logic_error);
    ASSERT_THROW(vec_invalid.collinear_with(vec_valid), std::logic_error);

    ASSERT_THROW(vec_valid.orthogonal_to(vec_invalid), std::logic_error);
    ASSERT_THROW(vec_invalid.orthogonal_to(vec_valid), std::logic_error);
}