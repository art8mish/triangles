#include <fstream>
#include <gtest/gtest.h>

#include "point.hpp"
#include "triangles.hpp"
#include "octo_tree.hpp"

using triangles::nan;

class TestOctoTree : public ::testing::Test {
protected:
    using OctoTree = typename triangles::OctoTree<double>;
    using Triangle = typename triangles::Triangle<double>;
    using Point = typename triangles::Point<double>;

    Point p_zero{};
    Point p_min {-5, -5, -5};
    Point p_max {5, 5, 5};

    Point p_octI_1 {2, 1, 1};
    Point p_octI_2 {1, 2, 1};
    Point p_octI_3 {1, 1, 2};

    Point p_octII_1 {2, -1, 1};
    Point p_octII_2 {1, -2, 1};
    Point p_octII_3 {1, -1, 2};

    Point p_octIII_1 {2, -1, -1};
    Point p_octIII_2 {1, -2, -1};
    Point p_octIII_3 {1, -1, -2};

    Point p_octIV_1 {2, 1, -1};
    Point p_octIV_2 {1, 2, -1};
    Point p_octIV_3 {1, 1, -2};

    Point p_octV_1 {-2, 1, 1};
    Point p_octV_2 {-1, 2, 1};
    Point p_octV_3 {-1, 1, 2};

    Point p_octVI_1 {-2, -1, 1};
    Point p_octVI_2 {-1, -2, 1};
    Point p_octVI_3 {-1, -1, 2};

    Point p_octVII_1 {-2, -1, -1};
    Point p_octVII_2 {-1, -2, -1};
    Point p_octVII_3 {-1, -1, -2};

    Point p_octVIII_1 {-2, 1, -1};
    Point p_octVIII_2 {-1, 2, -1};
    Point p_octVIII_3 {-1, 1, -2};

    Triangle tr_octI {p_octI_1, p_octI_2, p_octI_3};
    Triangle tr_octII {p_octII_1, p_octII_2, p_octII_3};
    Triangle tr_octIII {p_octIII_1, p_octIII_2, p_octIII_3};
    Triangle tr_octIV {p_octIV_1, p_octIV_2, p_octIV_3};
    Triangle tr_octV {p_octV_1, p_octV_2, p_octV_3};
    Triangle tr_octVI {p_octVI_1, p_octVI_2, p_octVI_3};
    Triangle tr_octVII {p_octVII_1, p_octVII_2, p_octVII_3};
    Triangle tr_octVIII {p_octVIII_1, p_octVIII_2, p_octVIII_3};

    void SetUp() {
    }
    void TearDown() {
    }
};

TEST_F(TestOctoTree, DefaultInit) {
    OctoTree tree{p_min, p_max};
    tree.add_triangle(tr_octI);
    tree.add_triangle(tr_octII);
    tree.add_triangle(tr_octIII);
    tree.add_triangle(tr_octIV);
    tree.add_triangle(tr_octV);
    tree.add_triangle(tr_octVI);
    tree.add_triangle(tr_octVII);
    tree.add_triangle(tr_octVIII);

    const auto &intersections = tree.intersections();
    ASSERT_EQ(intersections.size(), 0);
}

TEST_F(TestOctoTree, IntersectionDepth2) {
    OctoTree tree{p_min, p_max};
    tree.add_triangle(tr_octI);
    tree.add_triangle(tr_octII);
    tree.add_triangle(tr_octIII);
    tree.add_triangle(tr_octIV);
    tree.add_triangle(tr_octV);
    tree.add_triangle(tr_octVI);
    tree.add_triangle(tr_octVII);
    tree.add_triangle(tr_octVIII);
    tree.add_triangle(tr_octVIII);

    Triangle tr_oct_II_III {p_octII_1, p_octII_2, p_octIII_3};
    tree.add_triangle(tr_oct_II_III);
    const auto &intersections = tree.intersections();

    ASSERT_EQ(intersections.size(), 5);
    ASSERT_TRUE(intersections.contains(1));
    ASSERT_TRUE(intersections.contains(2));
    ASSERT_TRUE(intersections.contains(7));
    ASSERT_TRUE(intersections.contains(8));
    ASSERT_TRUE(intersections.contains(9));
}


TEST_F(TestOctoTree, IntersectionDepth3) {
    OctoTree tree{p_min, p_max};
    tree.add_triangle(tr_octI);
    tree.add_triangle(tr_octII);
    tree.add_triangle(tr_octIII);
    tree.add_triangle(tr_octIV);
    tree.add_triangle(tr_octV);
    tree.add_triangle(tr_octVI);
    tree.add_triangle(tr_octVII);
    tree.add_triangle(tr_octVIII);

    Triangle tr_oct_I_II {p_octI_1, p_octI_2, p_octII_3};
    for (unsigned i=0; i < 8; i++)
        tree.add_triangle(tr_oct_I_II);

    const auto &intersections = tree.intersections();

    ASSERT_EQ(intersections.size(), 10);
    ASSERT_TRUE(intersections.contains(0));
    ASSERT_TRUE(intersections.contains(1));
    for (unsigned i = 8; i < 16; ++i) {
        ASSERT_TRUE(intersections.contains(i));
    }
}
