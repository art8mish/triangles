    
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#include <../include/point.hpp>
#include <../include/vector.hpp>

class TestVector : public ::testing::Test
{
protected:
    using vec_t = typename triangles::Vector<>;
    using point_t = typename triangles::Point<>;
    
    void SetUp() {};
    void TearDown() {};
};

TEST_F(TestVector, Vector_Init) {
    vec_t vec_def {};
    ASSERT_EQ(false, vec_def.valid());
    ASSERT_EQ(false, vec_def.is_null());

    vec_t vec_delta {16.2, 7.56, 0.0};
    ASSERT_EQ(true, vec_delta.valid());
    ASSERT_EQ(false, vec_delta.is_null());

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points {p_from, p_to};
    ASSERT_EQ(true, vec_points.valid());
    ASSERT_EQ(false, vec_points.is_null());

    vec_t vec_nums {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_EQ(true, vec_nums.valid());
    ASSERT_EQ(false, vec_nums.is_null());
}

TEST_F(TestVector, Vector_Null) {
    vec_t vec_null_delta {0.0, 0.0, 0.0};
    ASSERT_EQ(true, vec_null_delta.valid());
    ASSERT_EQ(true, vec_null_delta.is_null());

    point_t p_null_from = {0.0, 0.0, 0.0};
    point_t p_null_to = {-0.0, 0.0, 0};
    vec_t vec_null_points {p_null_from, p_null_to};
    ASSERT_EQ(true, vec_null_points.valid());
    ASSERT_EQ(true, vec_null_points.is_null());

    vec_t vec_null_nums {0.0, 0.0, 0, 0.0, 0, 0};
    ASSERT_EQ(true, vec_null_nums.valid());
    ASSERT_EQ(true, vec_null_nums.is_null());

    vec_t vec_not_null {0.01, 0.0, 0.0};
    ASSERT_EQ(true, vec_not_null.valid());
    ASSERT_EQ(false, vec_not_null.is_null());
}

TEST_F(TestVector, Vector_Equal) {
    vec_t vec_null {0.0, 0.0, 0.0};
    vec_t vec_null_eq {0.0, 0.0, 0.0};
    ASSERT_EQ(true, vec_null == vec_null_eq);

    vec_t vec_null_neq {0.0, 0.0, 0.01};
    ASSERT_EQ(false, vec_null == vec_null_neq);

    vec_t vec_delta {16.2, 7.56, 0.0};
    vec_t vec_delta_eq {16.2, 7.56, 0.0};
    ASSERT_EQ(true, vec_delta == vec_delta_eq);

    vec_t vec_delta_neq {-16.2, 7.56, 0.0};
    ASSERT_EQ(false, vec_null == vec_null_neq);

    point_t p_from = {0.0, 0.0, 0.0};
    point_t p_to = {16.2, 7.56, -15.3};
    vec_t vec_points {p_from, p_to};
    vec_t vec_points_eq {p_from, p_to};
    ASSERT_EQ(true, vec_points == vec_points_eq);

    point_t p_to_neq = {16.2, 7.56, -15.31};
    vec_t vec_points_neq_1 {p_from, p_to_neq};
    ASSERT_EQ(false, vec_points == vec_points_neq_1);

    point_t p_from_neq = {0.0, 0.001, 0.0};
    vec_t vec_points_neq_2 {p_from_neq, p_to};
    ASSERT_EQ(false, vec_points == vec_points_neq_2);

    vec_t vec_nums {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    vec_t vec_nums_eq {0, 25.4, 6.7, 15.4, 94.3, 2.4};
    ASSERT_EQ(true, vec_nums == vec_nums_eq);

    vec_t vec_nums_neq {0, 25.4, 6.8, 15.4, 94.3, 2.4};
    ASSERT_EQ(false, vec_nums == vec_nums_neq);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}