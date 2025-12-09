#include <fstream>
#include <gtest/gtest.h>

#include <point.hpp>
#include <triangles.hpp>
#include <octo_tree.hpp>

using triangles::nan;

class TestOctoTree : public ::testing::Test {
protected:
    using OctoTree = typename triangles::TrianglesOctoTree<double>;
    using Triangle = typename triangles::Triangle<double>;
    using Point = typename triangles::Point<double>;

    Point p_zero{};

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

    void SetUp() {
    }
    void TearDown() {
    }
};

TEST_F(TestOctoTree, DefaultInit) {
    Triangle tr_octI {p_octI_1, p_octI_2, p_octI_3};
    Triangle tr_octII {p_octII_1, p_octII_2, p_octII_3};
    Triangle tr_octIII {p_octIII_1, p_octIII_2, p_octIII_3};
    Triangle tr_octIV {p_octIV_1, p_octIV_2, p_octIV_3};
    Triangle tr_octV {p_octV_1, p_octV_2, p_octV_3};
    Triangle tr_octVI {p_octVI_1, p_octVI_2, p_octVI_3};
    Triangle tr_octVII {p_octVII_1, p_octVII_2, p_octVII_3};
    Triangle tr_octVIII {p_octVIII_1, p_octVIII_2, p_octVIII_3};

    OctoTree tree{};
    tree.add_triangle(tr_octI);
    tree.add_triangle(tr_octII);
    tree.add_triangle(tr_octIII);
    tree.add_triangle(tr_octIV);
    tree.add_triangle(tr_octV);
    tree.add_triangle(tr_octVI);
    tree.add_triangle(tr_octVIII);
    tree.dump();
}
