#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>

#include <../include/point.hpp>

class TestPoint : public ::testing::Test
{
protected:
    using point_t = typename triangles::Point<>;
    using point_float_t = typename triangles::Point<float>;
    using point_double_t = typename triangles::Point<double>;
    using point_ldouble_t = typename triangles::Point<long double>;

    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestPoint, Point_DefaultInit) {
    point_t p_def1 {};
    ASSERT_EQ(false, p_def1.valid());
    ASSERT_EQ(false, p_def1.is_null());

    point_t p_def2 {};
    ASSERT_EQ(false, p_def1 == p_def2);
}

TEST_F(TestPoint, Point_Null_Int) {
    point_t p_null_int {0, 0, 0};
    ASSERT_EQ(true, p_null_int.valid());
    ASSERT_EQ(true, p_null_int.is_null());

    point_t p_1null_int_0 {0, -734, 632};
    ASSERT_EQ(true, p_1null_int_0.valid());
    ASSERT_EQ(false, p_1null_int_0.is_null());

    point_t p_1null_int_1 {152, 0, 446};
    ASSERT_EQ(true, p_1null_int_1.valid());
    ASSERT_EQ(false, p_1null_int_1.is_null());

    point_t p_1null_int_2 {-562, 242, 0};
    ASSERT_EQ(true, p_1null_int_2.valid());
    ASSERT_EQ(false, p_1null_int_2.is_null());

    point_t p_2null_int_0 {0, 0, 446};
    ASSERT_EQ(true, p_2null_int_0.valid());
    ASSERT_EQ(false, p_2null_int_0.is_null());

    point_t p_2null_int_1 {0, -242, 0};
    ASSERT_EQ(true, p_2null_int_1.valid());
    ASSERT_EQ(false, p_2null_int_1.is_null());

    point_t p_2null_int_2 {562, 0, 0};
    ASSERT_EQ(true, p_2null_int_2.valid());
    ASSERT_EQ(false, p_2null_int_2.is_null());
}

TEST_F(TestPoint, Point_Null_Float) {
    point_float_t p_null_float {0.0f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_null_float.valid());
    ASSERT_EQ(true, p_null_float.is_null());

    point_float_t p_1null_float_0 {0.0f, 26.26f, -174.32f};
    ASSERT_EQ(true, p_1null_float_0.valid());
    ASSERT_EQ(false, p_1null_float_0.is_null());

    point_float_t p_1null_float_1 {26.211f, 0.0f, 125.3f};
    ASSERT_EQ(true, p_1null_float_1.valid());
    ASSERT_EQ(false, p_1null_float_1.is_null());

    point_float_t p_1null_float_2 {-152.2f, 833.516f, 0.0f};
    ASSERT_EQ(true, p_1null_float_2.valid());
    ASSERT_EQ(false, p_1null_float_2.is_null());

    point_float_t p_2null_float_0 {0.0f, 0.0f, 174.32f};
    ASSERT_EQ(true, p_2null_float_0.valid());
    ASSERT_EQ(false, p_2null_float_0.is_null());

    point_float_t p_2null_float_1 {0.0f, -26.26f, 0.0f};
    ASSERT_EQ(true, p_2null_float_1.valid());
    ASSERT_EQ(false, p_2null_float_1.is_null());

    point_float_t p_2null_float_2 {152.2f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_2null_float_2.valid());
    ASSERT_EQ(false, p_2null_float_2.is_null());
}

TEST_F(TestPoint, Point_Null_Double) {
    point_double_t p_null_double {0.0, -0.0, 0.0};
    ASSERT_EQ(true, p_null_double.valid());
    ASSERT_EQ(true, p_null_double.is_null());

    point_double_t p_1null_double_0 {0.0, 51.2, 174.32};
    ASSERT_EQ(true, p_1null_double_0.valid());
    ASSERT_EQ(false, p_1null_double_0.is_null());

    point_double_t p_1null_double_1 {26.211, 0.0, 125.3};
    ASSERT_EQ(true, p_1null_double_1.valid());
    ASSERT_EQ(false, p_1null_double_1.is_null());

    point_double_t p_1null_double_2 {152.2, -833.516, 0.0};
    ASSERT_EQ(true, p_1null_double_2.valid());
    ASSERT_EQ(false, p_1null_double_2.is_null());

    point_double_t p_2null_double_0 {-0.0, 0.0, 174.32};
    ASSERT_EQ(true, p_2null_double_0.valid());
    ASSERT_EQ(false, p_2null_double_0.is_null());

    point_double_t p_2null_double_1 {0.0, 51.2, 0.0};
    ASSERT_EQ(true, p_2null_double_1.valid());
    ASSERT_EQ(false, p_2null_double_1.is_null());

    point_double_t p_2null_double_2 {152.2, 0.0, 0.0};
    ASSERT_EQ(true, p_2null_double_2.valid());
    ASSERT_EQ(false, p_2null_double_2.is_null());
}


TEST_F(TestPoint, Point_Null_LongDouble) {
    point_ldouble_t p_null_ldouble {0.0L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_null_ldouble.valid());
    ASSERT_EQ(true, p_null_ldouble.is_null());

    point_ldouble_t p_1null_ldouble_0 {0.0L, 51.2L, -174.32L};
    ASSERT_EQ(true, p_1null_ldouble_0.valid());
    ASSERT_EQ(false, p_1null_ldouble_0.is_null());

    point_ldouble_t p_1null_ldouble_1 {-26.211L, 0.0L, 125.3L};
    ASSERT_EQ(true, p_1null_ldouble_1.valid());
    ASSERT_EQ(false, p_1null_ldouble_1.is_null());

    point_ldouble_t p_1null_ldouble_2 {152.2L, 833.516L, 0.0L};
    ASSERT_EQ(true, p_1null_ldouble_2.valid());
    ASSERT_EQ(false, p_1null_ldouble_2.is_null());

    point_ldouble_t p_2null_ldouble_0 {0.0L, -0.0L, 174.32L};
    ASSERT_EQ(true, p_2null_ldouble_0.valid());
    ASSERT_EQ(false, p_2null_ldouble_0.is_null());

    point_ldouble_t p_2null_ldouble_1 {0.0L, 51.2L, 0.0L};
    ASSERT_EQ(true, p_2null_ldouble_1.valid());
    ASSERT_EQ(false, p_2null_ldouble_1.is_null());

    point_ldouble_t p_2null_ldouble_2 {152.2L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_2null_ldouble_2.valid());
    ASSERT_EQ(false, p_2null_ldouble_2.is_null());
}

TEST_F(TestPoint, Point_Equal_Int) {
    point_t p_int {0, 734, -632};
    point_t p_int_eq {0, 734, -632};

    ASSERT_EQ(true, p_int == p_int_eq);

    point_t p_int_neq {1, 734, 632};
    ASSERT_EQ(false, p_int == p_int_neq);

    point_t p_null_int {0, 0, 0};
    point_t p_null_int_eq {0, 0, 0};
    ASSERT_EQ(true, p_null_int == p_null_int_eq);

    point_t p_null_int_neq {0, 0, 1};
    ASSERT_EQ(false, p_null_int == p_null_int_neq);
}

TEST_F(TestPoint, Point_Equal_Float) {
    point_float_t p_float {26.211f, -51.2f, 125.3f};
    point_float_t p_float_eq {26.211f, -51.2f, 125.3f};

    ASSERT_EQ(true, p_float == p_float_eq);

    point_float_t p_float_neq {26.211f, -51.3f, 125.3f};
    ASSERT_EQ(false, p_float == p_float_neq);

    point_float_t p_null_float {0.0f, 0.0f, -0.0f};
    point_float_t p_null_float_eq {0.0f, 0.0f, 0.0f};
    ASSERT_EQ(true, p_null_float == p_null_float_eq);

    point_float_t p_null_float_neq {0.01f, 0.0f, 0.0f};
    ASSERT_EQ(false, p_null_float == p_null_float_neq);
}


TEST_F(TestPoint, Point_Equal_Double) {
    point_double_t p_double {152.2, 833.516, 0.0};
    point_double_t p_double_eq {152.2, 833.516, 0.0};

    ASSERT_EQ(true, p_double == p_double_eq);

    point_double_t p_double_neq {26.211, 51.2, 125.3};
    ASSERT_EQ(false, p_double == p_double_neq);

    point_double_t p_null_double {0.0, 0.0, 0.0};
    point_double_t p_null_double_eq {0.0, 0.0, 0.0};
    ASSERT_EQ(true, p_null_double == p_null_double_eq);

    point_double_t p_null_double_neq {0.0, 0.0001, 0.0};
    ASSERT_EQ(false, p_null_double == p_null_double_neq);
}

TEST_F(TestPoint, Point_Equal_LongDouble) {
    point_ldouble_t p_ldouble {152.2L, 833.516, -14L};
    point_ldouble_t p_ldouble_eq {152.2L, 833.516, -14L};
    ASSERT_EQ(true, p_ldouble == p_ldouble_eq);
    point_ldouble_t p_ldouble_neq {152.6L, 833.516, -14L};
    ASSERT_EQ(false, p_ldouble == p_ldouble_neq);

    point_ldouble_t p_null_ldouble {0.0L, 0.0L, 0.0L};
    point_ldouble_t p_null_ldouble_eq {-0.0L, 0.0L, 0.0L};
    ASSERT_EQ(true, p_null_ldouble == p_null_ldouble_eq);

    point_ldouble_t p_null_ldouble_neq {0.0L, 0.0L, 0.00001L};
    ASSERT_EQ(false, p_null_ldouble == p_null_ldouble_neq);
}

TEST_F(TestPoint, Point_Valid_DiffTypes) {
    point_ldouble_t p_diff_types {15.3426L, 75.24, 88.15};
    ASSERT_EQ(true, p_diff_types.valid());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}