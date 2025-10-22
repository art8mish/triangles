#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>

using triangles::nan;

class TestPoint : public ::testing::Test
{
protected:
    using point_t = typename triangles::Point<double>;
    using point_float_t = typename triangles::Point<float>;
    using point_double_t = typename triangles::Point<double>;
    using point_ldouble_t = typename triangles::Point<long double>;

    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestPoint, DefaultInit) {
    point_t p_def1 {};
    ASSERT_EQ(true, p_def1.is_valid());
    ASSERT_EQ(true, p_def1.is_zero());

    point_t p_def2 {};
    ASSERT_EQ(true, p_def1 == p_def2);
}

TEST_F(TestPoint, Invalid) {
    point_t p_def1 {nan<double>(), 5.6, 10.43 };
    ASSERT_EQ(false, p_def1.is_valid());

    point_t p_def2 {0, 0, nan<double>()};
    ASSERT_EQ(false, p_def1.is_valid());
}

TEST_F(TestPoint, LowDimensions2D) {
    point_t point_2d_1 {5.2, 6.6};
    ASSERT_EQ(true, point_2d_1.is_valid());
    ASSERT_EQ(false, point_2d_1.is_zero());

    point_t point_2d_2 {5.2, 6.6, 0.0};
    ASSERT_EQ(true, point_2d_2.is_valid());
    ASSERT_EQ(false, point_2d_2.is_zero());
    
    ASSERT_EQ(true, point_2d_1 == point_2d_2);
}

TEST_F(TestPoint, LowDimensions1D) {
    point_t point_1d_1 {5.2};
    ASSERT_EQ(true, point_1d_1.is_valid());
    ASSERT_EQ(false, point_1d_1.is_zero());

    point_t point_1d_2 {5.2, 0.0};
    ASSERT_EQ(true, point_1d_2.is_valid());
    ASSERT_EQ(false, point_1d_2.is_zero());

    point_t point_1d_3 {5.2, 0.0, 0.0};
    ASSERT_EQ(true, point_1d_3.is_valid());
    ASSERT_EQ(false, point_1d_3.is_zero());
    
    ASSERT_EQ(true, point_1d_1 == point_1d_2);
    ASSERT_EQ(true, point_1d_2 == point_1d_3);
}

TEST_F(TestPoint, Zero_Int) {
    point_t p_zero_int {0, 0, 0};
    ASSERT_EQ(true, p_zero_int.is_valid());
    ASSERT_EQ(true, p_zero_int.is_zero());

    point_t p_1zero_int_0 {0, -734, 632};
    ASSERT_EQ(true, p_1zero_int_0.is_valid());
    ASSERT_EQ(false, p_1zero_int_0.is_zero());

    point_t p_1zero_int_1 {152, 0, 446};
    ASSERT_EQ(true, p_1zero_int_1.is_valid());
    ASSERT_EQ(false, p_1zero_int_1.is_zero());

    point_t p_1zero_int_2 {-562, 242, 0};
    ASSERT_EQ(true, p_1zero_int_2.is_valid());
    ASSERT_EQ(false, p_1zero_int_2.is_zero());

    point_t p_2zero_int_0 {0, 0, 446};
    ASSERT_EQ(true, p_2zero_int_0.is_valid());
    ASSERT_EQ(false, p_2zero_int_0.is_zero());

    point_t p_2zero_int_1 {0, -242, 0};
    ASSERT_EQ(true, p_2zero_int_1.is_valid());
    ASSERT_EQ(false, p_2zero_int_1.is_zero());

    point_t p_2zero_int_2 {562, 0, 0};
    ASSERT_EQ(true, p_2zero_int_2.is_valid());
    ASSERT_EQ(false, p_2zero_int_2.is_zero());
}

TEST_F(TestPoint, Zero_Float) {
    point_float_t p_zero_float {0.0f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_zero_float.is_valid());
    ASSERT_EQ(true, p_zero_float.is_zero());

    point_float_t p_1zero_float_0 {0.0f, 26.26f, -174.32f};
    ASSERT_EQ(true, p_1zero_float_0.is_valid());
    ASSERT_EQ(false, p_1zero_float_0.is_zero());

    point_float_t p_1zero_float_1 {26.211f, 0.0f, 125.3f};
    ASSERT_EQ(true, p_1zero_float_1.is_valid());
    ASSERT_EQ(false, p_1zero_float_1.is_zero());

    point_float_t p_1zero_float_2 {-152.2f, 833.516f, 0.0f};
    ASSERT_EQ(true, p_1zero_float_2.is_valid());
    ASSERT_EQ(false, p_1zero_float_2.is_zero());

    point_float_t p_2zero_float_0 {0.0f, 0.0f, 174.32f};
    ASSERT_EQ(true, p_2zero_float_0.is_valid());
    ASSERT_EQ(false, p_2zero_float_0.is_zero());

    point_float_t p_2zero_float_1 {0.0f, -26.26f, 0.0f};
    ASSERT_EQ(true, p_2zero_float_1.is_valid());
    ASSERT_EQ(false, p_2zero_float_1.is_zero());

    point_float_t p_2zero_float_2 {152.2f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_2zero_float_2.is_valid());
    ASSERT_EQ(false, p_2zero_float_2.is_zero());
}

TEST_F(TestPoint, Zero_Double) {
    point_double_t p_zero_double {0.0, -0.0, 0.0};
    ASSERT_EQ(true, p_zero_double.is_valid());
    ASSERT_EQ(true, p_zero_double.is_zero());

    point_double_t p_1zero_double_0 {0.0, 51.2, 174.32};
    ASSERT_EQ(true, p_1zero_double_0.is_valid());
    ASSERT_EQ(false, p_1zero_double_0.is_zero());

    point_double_t p_1zero_double_1 {26.211, 0.0, 125.3};
    ASSERT_EQ(true, p_1zero_double_1.is_valid());
    ASSERT_EQ(false, p_1zero_double_1.is_zero());

    point_double_t p_1zero_double_2 {152.2, -833.516, 0.0};
    ASSERT_EQ(true, p_1zero_double_2.is_valid());
    ASSERT_EQ(false, p_1zero_double_2.is_zero());

    point_double_t p_2zero_double_0 {-0.0, 0.0, 174.32};
    ASSERT_EQ(true, p_2zero_double_0.is_valid());
    ASSERT_EQ(false, p_2zero_double_0.is_zero());

    point_double_t p_2zero_double_1 {0.0, 51.2, 0.0};
    ASSERT_EQ(true, p_2zero_double_1.is_valid());
    ASSERT_EQ(false, p_2zero_double_1.is_zero());

    point_double_t p_2zero_double_2 {152.2, 0.0, 0.0};
    ASSERT_EQ(true, p_2zero_double_2.is_valid());
    ASSERT_EQ(false, p_2zero_double_2.is_zero());
}


TEST_F(TestPoint, Zero_LongDouble) {
    point_ldouble_t p_zero_ldouble {0.0L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_zero_ldouble.is_valid());
    ASSERT_EQ(true, p_zero_ldouble.is_zero());

    point_ldouble_t p_1zero_ldouble_0 {0.0L, 51.2L, -174.32L};
    ASSERT_EQ(true, p_1zero_ldouble_0.is_valid());
    ASSERT_EQ(false, p_1zero_ldouble_0.is_zero());

    point_ldouble_t p_1zero_ldouble_1 {-26.211L, 0.0L, 125.3L};
    ASSERT_EQ(true, p_1zero_ldouble_1.is_valid());
    ASSERT_EQ(false, p_1zero_ldouble_1.is_zero());

    point_ldouble_t p_1zero_ldouble_2 {152.2L, 833.516L, 0.0L};
    ASSERT_EQ(true, p_1zero_ldouble_2.is_valid());
    ASSERT_EQ(false, p_1zero_ldouble_2.is_zero());

    point_ldouble_t p_2zero_ldouble_0 {0.0L, -0.0L, 174.32L};
    ASSERT_EQ(true, p_2zero_ldouble_0.is_valid());
    ASSERT_EQ(false, p_2zero_ldouble_0.is_zero());

    point_ldouble_t p_2zero_ldouble_1 {0.0L, 51.2L, 0.0L};
    ASSERT_EQ(true, p_2zero_ldouble_1.is_valid());
    ASSERT_EQ(false, p_2zero_ldouble_1.is_zero());

    point_ldouble_t p_2zero_ldouble_2 {152.2L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_2zero_ldouble_2.is_valid());
    ASSERT_EQ(false, p_2zero_ldouble_2.is_zero());
}

TEST_F(TestPoint, Equal_Int) {
    point_t p_int {0, 734, -632};
    ASSERT_EQ(true, p_int == p_int);

    point_t p_int_eq {0, 734, -632};
    ASSERT_EQ(true, p_int == p_int_eq);
    ASSERT_EQ(false, p_int != p_int_eq);
    ASSERT_EQ(true, (p_int == p_int_eq) == (p_int_eq == p_int));
    ASSERT_EQ(true, (p_int != p_int_eq) == (p_int_eq != p_int));


    point_t p_int_neq {1, 734, 632};
    ASSERT_EQ(false, p_int == p_int_neq);
    ASSERT_EQ(true, p_int != p_int_neq);
    ASSERT_EQ(true, (p_int == p_int_neq) == (p_int_neq == p_int));
    ASSERT_EQ(true, (p_int != p_int_neq) == (p_int_neq != p_int));

    point_t p_zero_int {0, 0, 0};
    point_t p_zero_int_eq {0, 0, 0};
    ASSERT_EQ(true, p_zero_int == p_zero_int_eq);
    ASSERT_EQ(false, p_zero_int != p_zero_int_eq);

    point_t p_zero_int_neq {0, 0, 1};
    ASSERT_EQ(false, p_zero_int == p_zero_int_neq);
    ASSERT_EQ(true, p_zero_int != p_zero_int_neq);
}

TEST_F(TestPoint, Equal_Float) {
    point_float_t p_float {26.211f, -51.2f, 125.3f};
    ASSERT_EQ(true, p_float == p_float);

    point_float_t p_float_eq {26.211f, -51.2f, 125.3f};
    ASSERT_EQ(true, p_float == p_float_eq);
    ASSERT_EQ(false, p_float != p_float_eq);
    ASSERT_EQ(true, (p_float == p_float_eq) == (p_float_eq == p_float));
    ASSERT_EQ(true, (p_float != p_float_eq) == (p_float_eq != p_float));

    point_float_t p_float_neq {26.211f, -51.3f, 125.3f};
    ASSERT_EQ(false, p_float == p_float_neq);
    ASSERT_EQ(true, p_float != p_float_neq);
    ASSERT_EQ(true, (p_float == p_float_neq) == (p_float_neq == p_float));
    ASSERT_EQ(true, (p_float != p_float_neq) == (p_float_neq != p_float));

    point_float_t p_zero_float {0.0f, 0.0f, -0.0f};
    point_float_t p_zero_float_eq {0.0f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_zero_float == p_zero_float_eq);
    ASSERT_EQ(false, p_zero_float != p_zero_float_eq);

    point_float_t p_zero_float_neq {0.01f, 0.0f, 0.0f};
    ASSERT_EQ(false, p_zero_float == p_zero_float_neq);
    ASSERT_EQ(true, p_zero_float != p_zero_float_neq);
}


TEST_F(TestPoint, Equal_Double) {
    point_double_t p_double {152.2, 833.516, 0.0};
    ASSERT_EQ(true, p_double == p_double);

    point_double_t p_double_eq {152.2, 833.516, 0.0};
    ASSERT_EQ(true, p_double == p_double_eq);
    ASSERT_EQ(false, p_double != p_double_eq);

    ASSERT_EQ(true, (p_double == p_double_eq) == (p_double_eq == p_double));
    ASSERT_EQ(true, (p_double != p_double_eq) == (p_double_eq != p_double));

    point_double_t p_double_neq {26.211, 51.2, 125.3};
    ASSERT_EQ(false, p_double == p_double_neq);
    ASSERT_EQ(true, p_double != p_double_neq);

    ASSERT_EQ(true, (p_double == p_double_neq) == (p_double_neq == p_double));
    ASSERT_EQ(true, (p_double != p_double_neq) == (p_double_neq != p_double));

    point_double_t p_zero_double {0.0, 0.0, 0.0};
    point_double_t p_zero_double_eq {0.0, 0.0, 0.0};
    ASSERT_EQ(true, p_zero_double == p_zero_double_eq);
    ASSERT_EQ(false, p_zero_double != p_zero_double_eq);

    point_double_t p_zero_double_neq {0.0, 0.0001, 0.0};
    ASSERT_EQ(false, p_zero_double == p_zero_double_neq);
    ASSERT_EQ(true, p_zero_double != p_zero_double_neq);
}

TEST_F(TestPoint, Equal_LongDouble) {
    point_ldouble_t p_ldouble {152.2L, 833.516, -14L};
    ASSERT_EQ(true, p_ldouble == p_ldouble);
    
    point_ldouble_t p_ldouble_eq {152.2L, 833.516, -14L};
    ASSERT_EQ(true, p_ldouble == p_ldouble_eq);
    ASSERT_EQ(false, p_ldouble != p_ldouble_eq);
    ASSERT_EQ(true, (p_ldouble == p_ldouble_eq) == (p_ldouble_eq == p_ldouble));
    ASSERT_EQ(true, (p_ldouble != p_ldouble_eq) == (p_ldouble_eq != p_ldouble));
    

    point_ldouble_t p_ldouble_neq {152.6L, 833.516, -14L};
    ASSERT_EQ(false, p_ldouble == p_ldouble_neq);
    ASSERT_EQ(true, p_ldouble != p_ldouble_neq);
    ASSERT_EQ(true, (p_ldouble == p_ldouble_neq) == (p_ldouble_neq == p_ldouble));
    ASSERT_EQ(true, (p_ldouble != p_ldouble_neq) == (p_ldouble_neq != p_ldouble));

    point_ldouble_t p_zero_ldouble {0.0L, 0.0L, 0.0L};
    point_ldouble_t p_zero_ldouble_eq {-0.0L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_zero_ldouble == p_zero_ldouble_eq);
    ASSERT_EQ(false, p_zero_ldouble != p_zero_ldouble_eq);

    point_ldouble_t p_zero_ldouble_neq {0.0L, 0.0L, 0.00001L};
    ASSERT_EQ(false, p_zero_ldouble == p_zero_ldouble_neq);
    ASSERT_EQ(true, p_zero_ldouble != p_zero_ldouble_neq);
}

TEST_F(TestPoint, is_valid_DiffTypes) {
    point_ldouble_t p_diff_types {15.3426L, 75.24, 88.15};
    ASSERT_EQ(true, p_diff_types.is_valid());
}
