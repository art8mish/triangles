    
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>
#include <vector.hpp>
#include <utils.hpp>

using triangles::zero;
using triangles::equal;

class TestVector : public ::testing::Test
{
protected:
    using vec_t = typename triangles::Vector<double>;
    using point_t = typename triangles::Point<double>;
    double eps_ = triangles::get_epsilon<double>();

    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestVector, Init) {
    vec_t vec_def_zero1 {};
    ASSERT_EQ(true, vec_def_zero1.is_valid());
    ASSERT_EQ(true, vec_def_zero1.is_zero());

    vec_t vec_delta {16.2, 7.56, 0.0};
    ASSERT_EQ(true, vec_delta.is_valid());
    ASSERT_EQ(false, vec_delta.is_zero());

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points {p_from, p_to};
    ASSERT_EQ(true, vec_points.is_valid());
    ASSERT_EQ(false, vec_points.is_zero());

    vec_t vec_nums {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_EQ(true, vec_nums.is_valid());
    ASSERT_EQ(false, vec_nums.is_zero());
}



TEST_F(TestVector, IsZero) {
    vec_t vec_def_zero1 {};
    ASSERT_EQ(true, vec_def_zero1.is_valid());
    ASSERT_EQ(true, vec_def_zero1.is_zero());

    vec_t vec_zero_delta {0.0, 0.0, 0.0};
    ASSERT_EQ(true, vec_zero_delta.is_valid());
    ASSERT_EQ(true, vec_zero_delta.is_zero());

    point_t p_zero_from = {0.0, 0.0, 0.0};
    point_t p_zero_to = {-0.0, 0.0, 0};
    vec_t vec_zero_points {p_zero_from, p_zero_to};
    ASSERT_EQ(true, vec_zero_points.is_valid());
    ASSERT_EQ(true, vec_zero_points.is_zero());

    vec_t vec_zero_nums {0.0, 0.0, 0, 0.0, 0, 0};
    ASSERT_EQ(true, vec_zero_nums.is_valid());
    ASSERT_EQ(true, vec_zero_nums.is_zero());

    vec_t vec_not_zero {0.01, 0.0, 0.0};
    ASSERT_EQ(true, vec_not_zero.is_valid());
    ASSERT_EQ(false, vec_not_zero.is_zero());
}

TEST_F(TestVector, LowDimensions) {
    vec_t vec_2d_1 {16.2, 7.56};
    ASSERT_EQ(true, vec_2d_1.is_valid());
    ASSERT_EQ(false, vec_2d_1.is_zero());

    vec_t vec_2d_2 {16.2, 7.56, 0.0};
    ASSERT_EQ(true, vec_2d_2.is_valid());
    ASSERT_EQ(false, vec_2d_2.is_zero());
    
    ASSERT_EQ(true, vec_2d_1 == vec_2d_2);

    vec_t vec_1d_1 {0.001};
    ASSERT_EQ(true, vec_1d_1.is_valid());
    ASSERT_EQ(false, vec_1d_1.is_zero());

    vec_t vec_1d_2 {0.001, 0.0};
    ASSERT_EQ(true, vec_1d_2.is_valid());
    ASSERT_EQ(false, vec_1d_2.is_zero());

    vec_t vec_1d_3 {0.001, 0.0, 0.0};
    ASSERT_EQ(true, vec_1d_3.is_valid());
    ASSERT_EQ(false, vec_1d_3.is_zero());
    
    ASSERT_EQ(true, vec_1d_1 == vec_1d_2);
    ASSERT_EQ(true, vec_1d_2 == vec_1d_3);
}

TEST_F(TestVector, Equality) {
    vec_t vec_zero {0.0, 0.0, 0.0};
    vec_t vec_zero_eq {0.0, 0.0, 0.0};
    ASSERT_EQ(true, vec_zero == vec_zero_eq);
    ASSERT_EQ(false, vec_zero != vec_zero_eq);

    vec_t vec_zero_neq {0.0, 0.0, 0.01};
    ASSERT_EQ(false, vec_zero == vec_zero_neq);
    ASSERT_EQ(true, vec_zero != vec_zero_neq);

    vec_t vec_delta {16.2, 7.56, 0.0};
    vec_t vec_delta_eq {16.2, 7.56, 0.0};
    ASSERT_EQ(true, vec_delta == vec_delta_eq);
    ASSERT_EQ(false, vec_delta != vec_delta_eq);

    vec_t vec_delta_neq {-16.2, 7.56, 0.0};
    ASSERT_EQ(false, vec_zero == vec_zero_neq);
    ASSERT_EQ(true, vec_zero != vec_zero_neq);

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points {p_from, p_to};
    vec_t vec_points_eq {p_from, p_to};
    ASSERT_EQ(true, vec_points == vec_points_eq);
    ASSERT_EQ(false, vec_points != vec_points_eq);

    point_t p_to_neq = {16.2, 7.56, -15.31};
    vec_t vec_points_neq_1 {p_from, p_to_neq};
    ASSERT_EQ(false, vec_points == vec_points_neq_1);
    ASSERT_EQ(true, vec_points != vec_points_neq_1);

    point_t p_from_neq = {0.0, 0.001, 0.0};
    vec_t vec_points_neq_2 {p_from_neq, p_to};
    ASSERT_EQ(false, vec_points == vec_points_neq_2);
    ASSERT_EQ(true, vec_points != vec_points_neq_2);

    vec_t vec_nums {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    vec_t vec_nums_eq {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_EQ(true, vec_nums == vec_nums_eq);
    ASSERT_EQ(false, vec_nums != vec_nums_eq);

    vec_t vec_nums_neq {0, 25.4, 6.8, 15.4, 94.3, 2.4};
    ASSERT_EQ(false, vec_nums == vec_nums_neq);
    ASSERT_EQ(true, vec_nums != vec_nums_neq);
}

TEST_F(TestVector, Edot) {
    vec_t vec_zero1 {};
    vec_t vec_zero2 {};
    ASSERT_EQ(true, zero(vec_zero1.edot(vec_zero2), eps_));

    vec_t vec_main {1, -2, 3};
    ASSERT_EQ(true,  zero(vec_main.edot(vec_zero1), eps_));
    ASSERT_EQ(true,  zero(vec_zero1.edot(vec_main), eps_));

    vec_t vec1 {1, 2, 1};
    ASSERT_EQ(true, zero(vec_main.edot(vec1), eps_));
    ASSERT_EQ(true, zero(vec1.edot(vec_main), eps_));

    vec_t vec2 {3, 2, 1};
    ASSERT_EQ(true, equal(vec_main.edot(vec2), 2.0, eps_));
    ASSERT_EQ(true, equal(vec_main.edot(vec2), vec2.edot(vec_main), eps_));

    vec_t vec3 {0, 0, 1};
    ASSERT_EQ(true, equal(vec_main.edot(vec3), 3.0, eps_));
    ASSERT_EQ(true, equal(vec_main.edot(vec3), vec3.edot(vec_main), eps_));
}

TEST_F(TestVector, Ecross) {
    vec_t vec_zero1 {};
    vec_t vec_zero2 {};
    ASSERT_EQ(true, vec_zero1.ecross(vec_zero2).is_zero());

    vec_t vec_main {1, -2, 3};
    ASSERT_EQ(true,  vec_main.ecross(vec_zero1).is_zero());
    ASSERT_EQ(true,  vec_zero1.ecross(vec_main).is_zero());

    vec_t vec_col {2, -4, 6};
    ASSERT_EQ(true, vec_main.ecross(vec_col).is_zero());
    ASSERT_EQ(true, vec_col.ecross(vec_main).is_zero());

    vec_t vec2 {5, 1, 2};
    ASSERT_EQ(true, (vec_main.ecross(vec2) == vec_t {-7, 13, 11}));
    ASSERT_EQ(true, (vec2.ecross(vec_main) == vec_t {7, -13, -11}));

    vec_t vec3 {0, 0, 1};
    ASSERT_EQ(true, (vec_main.ecross(vec3) == vec_t {-2, -1, 0}));
    ASSERT_EQ(true, (vec3.ecross(vec_main) == vec_t {2, 1, 0}));
}


TEST_F(TestVector, Collinearity) {
    vec_t vec_zero1 {};
    vec_t vec_zero2 {};
    ASSERT_EQ(true, vec_zero1.collinear_with(vec_zero2));

    vec_t vec_main {2, 5, -3};
    ASSERT_EQ(true, vec_main.collinear_with(vec_zero1));

    vec_t vec_col1 {6, 15, -9};
    ASSERT_EQ(true, vec_main.collinear_with(vec_col1));

    vec_t vec_reverse1 {-2, -5, 3};
    ASSERT_EQ(true, vec_main.collinear_with(vec_reverse1));

    vec_t vec_reverse2 {-4, -10, 6};
    ASSERT_EQ(true, vec_main.collinear_with(vec_reverse2));

    vec_t vec_not_col {0, 5, 3};
    ASSERT_EQ(false, vec_main.collinear_with(vec_not_col));
}

TEST_F(TestVector, Orthogonality) {
    vec_t vec_zero1 {};
    vec_t vec_zero2 {};
    ASSERT_EQ(true, vec_zero1.orthogonal_to(vec_zero2));

    vec_t vec_main {2, 5, -3};
    ASSERT_EQ(true, vec_main.orthogonal_to(vec_zero1));

    vec_t vec_orthogonal {4, -1, 1};
    ASSERT_EQ(true, vec_main.orthogonal_to(vec_orthogonal));

    vec_t vec_not_orthogonal {-3, 2, 4};
    ASSERT_EQ(false, vec_main.orthogonal_to(vec_not_orthogonal));
}

TEST_F(TestVector, GetPerpendicular) {
    vec_t vec_zero {};
    ASSERT_EQ(true, vec_zero.get_perpendicular().is_zero());

    vec_t vec1 {2, 5, -3};
    vec_t vec_orth1 = vec1.get_perpendicular();
    ASSERT_EQ(true, vec1.orthogonal_to(vec_orth1));
    ASSERT_EQ(true, vec_orth1.orthogonal_to(vec1));

    vec_t vec2 {0, 1, 2};
    vec_t vec_orth2 = vec2.get_perpendicular();
    ASSERT_EQ(true, vec2.orthogonal_to(vec_orth2));
    ASSERT_EQ(true, vec_orth2.orthogonal_to(vec2));

    vec_t vec3 {0.001, 1, 0};
    vec_t vec_orth3 = vec3.get_perpendicular();
    ASSERT_EQ(true, vec3.orthogonal_to(vec_orth3));
    ASSERT_EQ(true, vec_orth3.orthogonal_to(vec3));

    vec_t vec4 {0.001, 0.001, 0.001};
    vec_t vec_orth4 = vec4.get_perpendicular();
    ASSERT_EQ(true, vec4.orthogonal_to(vec_orth4));
    ASSERT_EQ(true, vec_orth4.orthogonal_to(vec4));
}

TEST_F(TestVector, InvalidStateExceptions) {
    vec_t vec_invalid {1, 2, std::numeric_limits<double>::quiet_NaN()};
    ASSERT_EQ(false, vec_invalid.is_valid());

    EXPECT_THROW(vec_invalid.is_zero(), std::logic_error);
    EXPECT_THROW(vec_invalid.get_perpendicular(), std::logic_error);

    vec_t vec_valid {1, 2, 3};
    ASSERT_EQ(true, vec_valid.is_valid());

    EXPECT_THROW(vec_valid == vec_invalid, std::logic_error);
    EXPECT_THROW(vec_invalid == vec_valid, std::logic_error);

    EXPECT_THROW(vec_valid != vec_invalid, std::logic_error);
    EXPECT_THROW(vec_invalid != vec_valid, std::logic_error);

    EXPECT_THROW(vec_valid.edot(vec_invalid), std::logic_error);
    EXPECT_THROW(vec_invalid.edot(vec_valid), std::logic_error);

    EXPECT_THROW(vec_valid.ecross(vec_invalid), std::logic_error);
    EXPECT_THROW(vec_invalid.ecross(vec_valid), std::logic_error);

    EXPECT_THROW(vec_valid.collinear_with(vec_invalid), std::logic_error);
    EXPECT_THROW(vec_invalid.collinear_with(vec_valid), std::logic_error);

    EXPECT_THROW(vec_valid.orthogonal_to(vec_invalid), std::logic_error);
    EXPECT_THROW(vec_invalid.orthogonal_to(vec_valid), std::logic_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}