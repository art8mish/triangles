#include <gtest/gtest.h>
#include <fstream>

#include <point.hpp>
#include <triangles.hpp>
#include <utils.hpp>

using triangles::nan;

class TestTriangles : public ::testing::Test
{
protected:
    using point_t = typename triangles::Point<double>;
    using vec_t = typename triangles::Vector<double>;
    using line_t = typename triangles::Line<double>;
    using plane_t = typename triangles::Plane<double>;
    using tr_t = typename triangles::Triangle<double>;

    // vec_t = typename triangles::Vector<double>;
    point_t p_zero {};

    // see geogebra/segment_segment.ggb
    vec_t d_a {1, 2, 2};

    point_t p_a11 {1, 2, 3};
    line_t l_a1 {p_a11, d_a};
    point_t p_a12 {l_a1.get_point(0.5)};
    point_t p_a13 {l_a1.get_point(1)};
    point_t p_a14 {l_a1.get_point(2)};
    point_t p_a15 {l_a1.get_point(3)};
    point_t p_a16 {l_a1.get_point(4)};
    point_t p_a17 {l_a1.get_point(5)};
    
    vec_t n {-2, 0.5, 0.5};
    line_t l_na {p_a11, n};

    point_t p_a21 {l_na.get_point(1)};
    line_t l_a2 {p_a21, d_a};
    point_t p_a22 {l_a2.get_point(0.5)};
    point_t p_a23 {l_a2.get_point(1)};
    point_t p_a24 {l_a2.get_point(2)};
    point_t p_a25 {l_a2.get_point(3)};
    point_t p_a26 {l_a2.get_point(4)};
    point_t p_a27 {l_a2.get_point(5)};

    point_t p_a31 {l_na.get_point(2)};
    line_t l_a3 {p_a31, d_a};
    point_t p_a32 {l_a3.get_point(0.5)};
    point_t p_a33 {l_a3.get_point(1)};
    point_t p_a34 {l_a3.get_point(2)};
    point_t p_a35 {l_a3.get_point(3)};
    point_t p_a36 {l_a3.get_point(4)};
    point_t p_a37 {l_a3.get_point(5)};


    point_t p_b11 {1, 3, 2};
    line_t l_b1 {p_b11, d_a};
    point_t p_b12 {l_b1.get_point(0.5)};
    point_t p_b13 {l_b1.get_point(1)};
    point_t p_b14 {l_b1.get_point(2)};
    point_t p_b15 {l_b1.get_point(3)};
    point_t p_b16 {l_b1.get_point(4)};
    point_t p_b17 {l_b1.get_point(5)};

    line_t l_nb {p_b11, n};
    point_t p_b31 {l_nb.get_point(2)};
    line_t l_b3 {p_b31, d_a};
    point_t p_b32 {l_b3.get_point(0.5)};
    point_t p_b33 {l_b3.get_point(1)};
    point_t p_b34 {l_b3.get_point(2)};
    point_t p_b35 {l_b3.get_point(3)};
    point_t p_b36 {l_b3.get_point(4)};
    point_t p_b37 {l_b3.get_point(5)};

    point_t p_d1 {1, 1, 4};
    line_t l_d {p_d1, d_a};
    point_t p_d2 {l_d.get_point(0.5)};
    point_t p_d3 {l_d.get_point(1)};
    point_t p_d4 {l_d.get_point(2)};
    point_t p_d5 {l_d.get_point(3)};
    point_t p_d55 {l_d.get_point(3.5)}; // between d5 and d6
    point_t p_d6 {l_d.get_point(4)};
    point_t p_d7 {l_d.get_point(5)};

    vec_t d_c {1, 3, 1};

    point_t p_c11 {1, 4, 1};
    line_t l_c1 {p_c11, d_c};
    point_t p_c12 {l_c1.get_point(0.5)};
    point_t p_c13 {l_c1.get_point(1)};
    point_t p_c14 {l_c1.get_point(2)};
    point_t p_c15 {l_c1.get_point(3)};
    point_t p_c16 {l_c1.get_point(4)};
    point_t p_c17 {l_c1.get_point(5)};

    line_t l_nc {p_c11, n};
    point_t p_c21 {l_nc.get_point(1)};
    line_t l_c2 {p_c21, d_c};
    point_t p_c22 {l_c2.get_point(0.5)};
    point_t p_c23 {l_c2.get_point(1)};
    point_t p_c24 {l_c2.get_point(2)};
    point_t p_c25 {l_c2.get_point(3)};
    point_t p_c26 {l_c2.get_point(4)};
    point_t p_c27 {l_c2.get_point(5)};

    point_t p_c31 {l_nc.get_point(2)};
    line_t l_c3 {p_c31, d_c};
    point_t p_c32 {l_c3.get_point(0.5)};
    point_t p_c33 {l_c3.get_point(1)};
    point_t p_c34 {l_c3.get_point(2)};
    point_t p_c35 {l_c3.get_point(3)};
    point_t p_c36 {l_c3.get_point(4)};
    point_t p_c37 {l_c3.get_point(5)};

    point_t p_e11 {1, 5, 0};
    line_t l_e1 {p_e11, d_c};
    point_t p_e12 {l_e1.get_point(0.5)};
    point_t p_e125 {l_e1.get_point(0.75)};
    point_t p_e13 {l_e1.get_point(1)};
    point_t p_e14 {l_e1.get_point(2)};
    point_t p_e15 {l_e1.get_point(3)};
    point_t p_e16 {l_e1.get_point(4)};
    point_t p_e165 {l_e1.get_point(4.5)}; //between e16 and e17
    point_t p_e17 {l_e1.get_point(5)};

    line_t l_ne {p_e11, n};
    point_t p_e31 {l_ne.get_point(2)};
    line_t l_e3 {p_e31, d_c};
    point_t p_e32 {l_e3.get_point(0.5)};
    point_t p_e325 {l_e3.get_point(0.75)};
    point_t p_e33 {l_e3.get_point(1)};
    point_t p_e34 {l_e3.get_point(2)};
    point_t p_e35 {l_e3.get_point(3)};
    point_t p_e36 {l_e3.get_point(4)};
    point_t p_e365 {l_e3.get_point(4.5)}; //between e36 and e37
    point_t p_e37 {l_e3.get_point(5)};

    tr_t seg_a1 {p_a11, p_a14, p_a15};
    tr_t seg_a3 {p_a31, p_a34, p_a35};

    void SetUp() {}
    void TearDown() {}

    void SegmentSegmentIntersection(
        const point_t& p_1n, const point_t& p_2n, const point_t& p_3n, const point_t& p_end, 
        const bool sec, const bool contain_p1, const bool contain_p2, 
        const std::string& context = "") {
        std::string context_msg{"Test: SegmentSegment"};
        context_msg += context;

        tr_t seg1 {p_1n, p_1n, p_end};
        tr_t seg2 {p_2n, p_2n, p_end};
        tr_t seg3 {p_3n, p_end, p_end};

        EXPECT_EQ(seg1.type(), tr_t::Kind::SEGMENT) << context_msg;
        EXPECT_EQ(seg2.type(), tr_t::Kind::SEGMENT) << context_msg;
        EXPECT_EQ(seg3.type(), tr_t::Kind::SEGMENT) << context_msg;

        EXPECT_EQ(sec, seg1.intersects(seg_a1)) << context_msg;
        EXPECT_EQ(sec, seg_a1.intersects(seg1)) << context_msg;

        // paral
        EXPECT_FALSE(seg1.intersects(seg_a3)) << context_msg;
        EXPECT_FALSE(seg_a3.intersects(seg1)) << context_msg;

        // arbitrary
        EXPECT_FALSE(seg2.intersects(seg_a3)) << context_msg;
        EXPECT_FALSE(seg_a3.intersects(seg2)) << context_msg;

        // touch
        EXPECT_EQ(contain_p1, seg3.intersects(seg_a3)) << context_msg;
        EXPECT_EQ(contain_p1, seg_a3.intersects(seg3)) << context_msg;

        EXPECT_EQ(contain_p2, seg3.intersects(seg_a1)) << context_msg;
        EXPECT_EQ(contain_p2, seg_a1.intersects(seg3)) << context_msg;   
    }

    

    void TriangleSegmentIntersection(
        const point_t& p_1n, const point_t& p_2n, const point_t& p_3n,
        const point_t& p_end, const point_t& tr_p1, const point_t& tr_p3, const bool sec,
        const bool contain_p_n, const bool contain_p_end, const std::string& context = "") {

        std::string context_msg{"Test: TriangleSegment"};
        context_msg += context;

        tr_t seg1 {p_1n, p_1n, p_end};
        tr_t seg2 {p_2n, p_2n, p_end};
        tr_t seg3 {p_3n, p_end, p_end};
        std::cout << seg3.to_string() + '\n';

        EXPECT_EQ(seg1.type(), tr_t::Kind::SEGMENT) << context_msg;
        EXPECT_EQ(seg2.type(), tr_t::Kind::SEGMENT) << context_msg;
        EXPECT_EQ(seg3.type(), tr_t::Kind::SEGMENT) << context_msg;

        tr_t tr1 {p_a11, p_a15, tr_p1};
        tr_t tr3 {p_a31, p_a35, tr_p3};
        std::cout << tr1.to_string() + '\n';

        EXPECT_EQ(tr1.type(), tr_t::Kind::TRIANGLE) << context_msg;
        EXPECT_EQ(tr3.type(), tr_t::Kind::TRIANGLE) << context_msg;

        EXPECT_EQ(sec, seg1.intersects(tr1)) << context_msg;
        EXPECT_EQ(sec, tr1.intersects(seg1)) << context_msg;

        // paral
        EXPECT_FALSE(seg1.intersects(tr3)) << context_msg;
        EXPECT_FALSE(tr3.intersects(seg1)) << context_msg;

        // arbitrary
        EXPECT_FALSE(seg2.intersects(tr3)) << context_msg;
        EXPECT_FALSE(tr3.intersects(seg2)) << context_msg;

        // touch
        EXPECT_EQ(contain_p_n, seg3.intersects(tr3)) << context_msg;
        EXPECT_EQ(contain_p_n, tr3.intersects(seg3)) << context_msg;

        EXPECT_EQ(contain_p_end, seg3.intersects(tr1)) << context_msg;
        EXPECT_EQ(contain_p_end, tr1.intersects(seg3)) << context_msg;   
    }
};

TEST_F(TestTriangles, PlaneLineIntersectionPoint) {
    plane_t plane {p_a11, p_a12, p_b11};
    ASSERT_TRUE(plane.is_valid());
    std::cout << plane.to_string() + "\n";
    std::cout << l_na.to_string() + "\n";
    std::cout << tr_t::plane_line_intersection_point(plane, l_na).to_string() + "\n";
    ASSERT_TRUE(tr_t::plane_line_intersection_point(plane, l_na) == p_a11);
}


TEST_F(TestTriangles, InitInvalid) {
    point_t p_invalid {1, 2, nan<double>()};

    tr_t triangle {p_zero, p_invalid, p_a11};
    ASSERT_FALSE(triangle.is_valid());
}

TEST_F(TestTriangles, InitValid) {
    tr_t tr1 {p_zero, p_a11, p_b11};
    ASSERT_TRUE(tr1.is_valid());
    ASSERT_EQ(tr1.type(), tr_t::Kind::TRIANGLE);

    tr_t tr2 {p_b11, p_a11, p_zero};
    ASSERT_TRUE(tr2.is_valid());
    ASSERT_EQ(tr2.type(), tr_t::Kind::TRIANGLE);

    ASSERT_EQ(seg_a1.type(), tr_t::Kind::SEGMENT);
    ASSERT_EQ(seg_a3.type(), tr_t::Kind::SEGMENT);

    tr_t tr_seg1 {p_a11, p_a12, p_a13};
    ASSERT_TRUE(tr_seg1.is_valid());
    ASSERT_EQ(tr_seg1.type(), tr_t::Kind::SEGMENT);

    tr_t tr_seg2 {p_zero, p_zero, p_a11};
    ASSERT_TRUE(tr_seg2.is_valid());
    ASSERT_EQ(tr_seg2.type(), tr_t::Kind::SEGMENT);

    tr_t tr_seg3 {p_a11, p_zero, p_a11};
    ASSERT_TRUE(tr_seg3.is_valid());
    ASSERT_EQ(tr_seg3.type(), tr_t::Kind::SEGMENT);

    tr_t tr_seg4 {p_a11, p_a12, p_a12};
    ASSERT_TRUE(tr_seg4.is_valid());
    ASSERT_EQ(tr_seg4.type(), tr_t::Kind::SEGMENT);

    tr_t tr_p3 {p_a11, p_a11, p_a11};
    ASSERT_TRUE(tr_p3.is_valid());
    ASSERT_EQ(tr_p3.type(), tr_t::Kind::POINT);
}

TEST_F(TestTriangles, IntersectionPointPoint) {
    tr_t tr_zero {p_zero, p_zero, p_zero};
    ASSERT_EQ(tr_zero.type(), tr_t::Kind::POINT);

    tr_t tr_zero_sec {p_zero, p_zero, p_zero};
    ASSERT_EQ(tr_zero_sec.type(), tr_t::Kind::POINT);
    ASSERT_TRUE(tr_zero_sec.intersects(tr_zero));
    ASSERT_TRUE(tr_zero.intersects(tr_zero_sec));
    
    tr_t tr1 {p_a11, p_a11, p_a11};
    ASSERT_TRUE(tr1.type() == tr_t::Kind::POINT);
    ASSERT_FALSE(tr1.intersects(tr_zero));
    ASSERT_FALSE(tr_zero.intersects(tr1));

    tr_t tr1_sec {p_a11, p_a11, p_a11};
    ASSERT_EQ(tr1_sec.type(), tr_t::Kind::POINT);
    ASSERT_TRUE(tr1_sec.intersects(tr1));
    ASSERT_TRUE(tr1.intersects(tr1_sec));
    
    tr_t tr2 {p_a12, p_a12, p_a12};
    ASSERT_EQ(tr2.type(), tr_t::Kind::POINT);

    ASSERT_FALSE(tr2.intersects(tr_zero));
    ASSERT_FALSE(tr_zero.intersects(tr2));

    ASSERT_FALSE(tr2.intersects(tr1));
    ASSERT_FALSE(tr1.intersects(tr2));

    tr_t tr2_sec {p_a12, p_a12, p_a12};
    ASSERT_EQ(tr2_sec.type(), tr_t::Kind::POINT);
    ASSERT_TRUE(tr2_sec.intersects(tr2));
    ASSERT_TRUE(tr2.intersects(tr2_sec));
}

TEST_F(TestTriangles, IntersectionSegmentPoint) {

    tr_t trp_zero {p_zero, p_zero, p_zero};
    ASSERT_FALSE(seg_a1.intersects(trp_zero));
    ASSERT_FALSE(trp_zero.intersects(seg_a1));

    tr_t trp_a1 {p_a11, p_a11, p_a11};
    ASSERT_TRUE(seg_a1.intersects(trp_a1));
    ASSERT_TRUE(trp_a1.intersects(seg_a1));

    tr_t trp_a2 {p_a12, p_a12, p_a12};
    ASSERT_TRUE(seg_a1.intersects(trp_a2));
    ASSERT_TRUE(trp_a2.intersects(seg_a1));

    tr_t trp_a3 {p_a13, p_a13, p_a13};
    ASSERT_TRUE(seg_a1.intersects(trp_a3));
    ASSERT_TRUE(trp_a3.intersects(seg_a1));

    tr_t trp_a4 {p_a15, p_a15, p_a15};
    ASSERT_TRUE(seg_a1.intersects(trp_a4));
    ASSERT_TRUE(trp_a4.intersects(seg_a1));

    tr_t trp_a5 {p_a17, p_a17, p_a17};
    ASSERT_FALSE(seg_a1.intersects(trp_a5));
    ASSERT_FALSE(trp_a5.intersects(seg_a1));


    tr_t trp_b11 {p_b11, p_b11, p_b11};
    ASSERT_FALSE(seg_a1.intersects(trp_b11));
    ASSERT_FALSE(trp_b11.intersects(seg_a1));

    tr_t trp_b12 {p_b12, p_b12, p_b12};
    ASSERT_FALSE(seg_a1.intersects(trp_b12));
    ASSERT_FALSE(trp_b12.intersects(seg_a1));

    tr_t trp_b13 {p_b13, p_b13, p_b13};
    ASSERT_FALSE(seg_a1.intersects(trp_b13));
    ASSERT_FALSE(trp_b13.intersects(seg_a1));

    tr_t trp_b14 {p_b14, p_b14, p_b14};
    ASSERT_FALSE(seg_a1.intersects(trp_b14));
    ASSERT_FALSE(trp_b14.intersects(seg_a1));

    tr_t trp_b15 {p_b15, p_b15, p_b15};
    ASSERT_FALSE(seg_a1.intersects(trp_b15));
    ASSERT_FALSE(trp_b15.intersects(seg_a1));

    tr_t trp_b17 {p_b17, p_b17, p_b17};
    ASSERT_FALSE(seg_a1.intersects(trp_b17));
    ASSERT_FALSE(trp_b17.intersects(seg_a1));
}


TEST_F(TestTriangles, IntersectionTrianglePoint) {

    tr_t trp_zero {p_zero, p_zero, p_zero};
    ASSERT_FALSE(seg_a1.intersects(trp_zero));
    ASSERT_FALSE(trp_zero.intersects(seg_a1));

    tr_t tr1 {p_a11, p_c14, p_a15};
    ASSERT_EQ(tr1.type(), tr_t::Kind::TRIANGLE);
    tr_t tr2 {p_a21, p_c24, p_a25};
    ASSERT_EQ(tr2.type(), tr_t::Kind::TRIANGLE);

    tr_t trp_a1 {p_a11, p_a11, p_a11};
    ASSERT_TRUE(tr1.intersects(trp_a1));
    ASSERT_TRUE(trp_a1.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_a1));
    ASSERT_FALSE(trp_a1.intersects(tr2));
    
    
    tr_t trp_d2 {p_d2, p_d2, p_d2};
    ASSERT_FALSE(tr1.intersects(trp_d2));
    ASSERT_FALSE(trp_d2.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_d2));
    ASSERT_FALSE(trp_d2.intersects(tr2));

    tr_t trp_a2 {p_a12, p_a12, p_a12};
    ASSERT_TRUE(tr1.intersects(trp_a2));
    ASSERT_TRUE(trp_a2.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_a2));
    ASSERT_FALSE(trp_a2.intersects(tr2));

    tr_t trp_b12 {p_b12, p_b12, p_b12};
    ASSERT_TRUE(tr1.intersects(trp_b12));
    ASSERT_TRUE(trp_b12.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_b12));
    ASSERT_FALSE(trp_b12.intersects(tr2));

    tr_t trp_c2 {p_c12, p_c12, p_c12};
    ASSERT_FALSE(tr1.intersects(trp_c2));
    ASSERT_FALSE(trp_c2.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_c2));
    ASSERT_FALSE(trp_c2.intersects(tr2));


    tr_t trp_d4 {p_d4, p_d4, p_d4};
    ASSERT_FALSE(tr1.intersects(trp_d4));
    ASSERT_FALSE(trp_d4.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_d4));
    ASSERT_FALSE(trp_d4.intersects(tr2));

    tr_t trp_a4 {p_a14, p_a14, p_a14};
    ASSERT_TRUE(tr1.intersects(trp_a4));
    ASSERT_TRUE(trp_a4.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_a4));
    ASSERT_FALSE(trp_a4.intersects(tr2));

    tr_t trp_b14 {p_b14, p_b14, p_b14};
    ASSERT_TRUE(tr1.intersects(trp_b14));
    ASSERT_TRUE(trp_b14.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_b14));
    ASSERT_FALSE(trp_b14.intersects(tr2));

    tr_t trp_c14 {p_c14, p_c14, p_c14};
    ASSERT_TRUE(tr1.intersects(trp_c14));
    ASSERT_TRUE(trp_c14.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_c14));
    ASSERT_FALSE(trp_c14.intersects(tr2));


    tr_t trp_d5 {p_d5, p_d5, p_d5};
    ASSERT_FALSE(tr1.intersects(trp_d5));
    ASSERT_FALSE(trp_d5.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_d5));
    ASSERT_FALSE(trp_d5.intersects(tr2));

    tr_t trp_a5 {p_a15, p_a15, p_a15};
    ASSERT_TRUE(tr1.intersects(trp_a5));
    ASSERT_TRUE(trp_a5.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_a5));
    ASSERT_FALSE(trp_a5.intersects(tr2));

    tr_t trp_b15 {p_b15, p_b15, p_b15};
    ASSERT_FALSE(tr1.intersects(trp_b15));
    ASSERT_FALSE(trp_b15.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_b15));
    ASSERT_FALSE(trp_b15.intersects(tr2));

    tr_t trp_c5 {p_c15, p_c15, p_c15};
    ASSERT_FALSE(tr1.intersects(trp_c5));
    ASSERT_FALSE(trp_c5.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_c5));
    ASSERT_FALSE(trp_c5.intersects(tr2));


    tr_t trp_d7 {p_d7, p_d7, p_d7};
    ASSERT_FALSE(tr1.intersects(trp_d7));
    ASSERT_FALSE(trp_d7.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_d7));
    ASSERT_FALSE(trp_d7.intersects(tr2));

    tr_t trp_a7 {p_a17, p_a17, p_a17};
    ASSERT_FALSE(tr1.intersects(trp_a7));
    ASSERT_FALSE(trp_a7.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_a7));
    ASSERT_FALSE(trp_a7.intersects(tr2));

    tr_t trp_b17 {p_b17, p_b17, p_b17};
    ASSERT_FALSE(tr1.intersects(trp_b17));
    ASSERT_FALSE(trp_b17.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_b17));
    ASSERT_FALSE(trp_b17.intersects(tr2));

    tr_t trp_c7 {p_c17, p_c17, p_c17};
    ASSERT_FALSE(tr1.intersects(trp_c7));
    ASSERT_FALSE(trp_c7.intersects(tr1));
    ASSERT_FALSE(tr2.intersects(trp_c7));
    ASSERT_FALSE(trp_c7.intersects(tr2));
}

TEST_F(TestTriangles, IntersectionCustom) {
    tr_t tr {p_a11, p_a15, p_c13};
    tr_t seg {p_c32, p_c32, p_a12};

    ASSERT_TRUE(tr.intersects(seg));
}

TEST_F(TestTriangles, IntersectionSegmentSegmentPerpendicular) {
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d2, true, false, false, "PerpendicularSecInside");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_a12, true, false, true, "PerpendicularEndSecInside");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_b12, false, false, false, "PerpendicularNoSecInside");

    SegmentSegmentIntersection(p_c15, p_c25, p_c35, p_d5, true, false, false, "PerpendicularSecBoundary");
    SegmentSegmentIntersection(p_c15, p_c25, p_c35, p_a15, true, false, true, "PerpendicularEndSecBoundary");
    SegmentSegmentIntersection(p_c15, p_c25, p_c35, p_b15, false, false, false, "PerpendicularNoSecBoundary");

    SegmentSegmentIntersection(p_c17, p_c27, p_c37, p_d7, false, false, false, "PerpendicularSecOut");
    SegmentSegmentIntersection(p_c17, p_c27, p_c37, p_a17, false, false, false, "PerpendicularEndSecOut");
    SegmentSegmentIntersection(p_c17, p_c27, p_c37, p_b17, false, false, false, "PerpendicularNoSecOut");
}

TEST_F(TestTriangles, IntersectionSegmentSegmentParallel) {
    SegmentSegmentIntersection(p_a12, p_a22, p_a32, p_a13, true, true, true, "ParallelInside");
    SegmentSegmentIntersection(p_a12, p_a22, p_a32, p_a15, true, true, true, "ParallelInside1Boundary");
    SegmentSegmentIntersection(p_a11, p_a21, p_a31, p_a15, true, true, true, "ParallelInside2Boundaries");
    SegmentSegmentIntersection(p_a12, p_a22, p_a32, p_a16, true, true, false, "ParallelOverlap");
    SegmentSegmentIntersection(p_a15, p_a25, p_a35, p_a17, true, true, false, "ParallelOverlap1Boundary");
    SegmentSegmentIntersection(p_a16, p_a26, p_a36, p_a17, false, false, false, "ParallelOut");
}

TEST_F(TestTriangles, IntersectionSegmentSegmentAngular) {
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d3, true, false, false, "AngularSecInside");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_a13, true, false, true, "AngularEndSecInside");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_b13, false, false, false, "AngularNoSecInside");

    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d5, true, false, false, "AngularSecInside1Boundary");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_a15, true, false, true, "AngularEndSecInside1Boundary");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_b15, false, false, false, "AngularNoSecInside1Boundary");

    SegmentSegmentIntersection(p_c11, p_c21, p_c31, p_d5, true, false, false, "AngularSecInside2Boundaries");
    SegmentSegmentIntersection(p_c11, p_c21, p_c31, p_a15, true, false, true, "AngularEndSecInside2Boundaries");
    SegmentSegmentIntersection(p_c11, p_c21, p_c31, p_b15, false, false, false, "AngularNoSecInside2Boundaries");

    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d55, true, false, false, "AngularSecInOverlap");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d6, true, false, false, "AngularSecBoundaryOverlap");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_d7, false, false, false, "AngularSecOutOverlap");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_a16, false, false, false, "AngularEndSecOverlap");
    SegmentSegmentIntersection(p_c12, p_c22, p_c32, p_b16, false, false, false, "AngularNoSecOverlap");

    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_d5, false, false, false, "AngularSecOverlap1Boundary");
    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_a15, true, false, true, "AngularEndSecOverlap1Boundary");
    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_b15, false, false, false, "AngularNoSecOverlap1Boundary");

    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_d7, false, false, false, "AngularSecOut");
    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_a17, false, false, false, "AngularEndSecOut");
    SegmentSegmentIntersection(p_c16, p_c26, p_c36, p_b17, false, false, false, "AngularNoSecOut");
}

TEST_F(TestTriangles, IntersectionTriangleSegmentPerpendicularInside) {
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_d2, p_c13, p_c33, true, false, false, "PerpendicularSecInsideLeft");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_d2, p_c12, p_c32, true, true, false, "PerpendicularSecInsideMid");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_d2, p_e125, p_e325, true, true, false, "PerpendicularSecInsideMidUp");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_d2, p_e12, p_e32, true, true, false, "PerpendicularSecInsideRight");

    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_a12, p_c13, p_c33, true, false, true, "PerpendicularEndSecInsideLeft");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_a12, p_c12, p_c32, true, true, true, "PerpendicularEndSecInsideMid");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_a12, p_e125, p_e325, true, true, true, "PerpendicularEndSecInsideMidUp");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_a12, p_e12, p_e32, true, true, true, "PerpendicularEndSecInsideRight");

    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_c13, p_c33, true, false, false, "PerpendicularNoSecInsideCLeft");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_c12, p_c32, true, true, true, "PerpendicularNoSecInsideCMid");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_e125, p_e325, true, true, true, "PerpendicularNoSecInsideCMidUp");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_e12, p_e32, true, true, true, "PerpendicularNoSecInsideCRight");

    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_b11, p_b31, false, false, false, "PerpendicularNoSecInsideBLeft");
    TriangleSegmentIntersection(p_c12, p_c22, p_c32, p_b12, p_b12, p_b32, true, false, true, "PerpendicularNoSecInsideBMid");
}

TEST_F(TestTriangles, IntersectionTriangleSegmentPerpendicularBoundary) {
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_d5, p_c17, p_c37, true, false, false, "PerpendicularSecBoundaryLeft");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_d5, p_c15, p_c35, true, true, false, "PerpendicularSecBoundaryMid");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_d5, p_e165, p_e365, true, true, false, "PerpendicularSecBoundaryMidUp");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_d5, p_e16, p_e36, true, true, false, "PerpendicularSecBoundaryRight");

    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_a15, p_c17, p_c37, true, false, true, "PerpendicularEndSecBoundaryLeft");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_a15, p_c15, p_c35, true, true, true, "PerpendicularEndSecBoundaryMid");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_a15, p_e165, p_e365, true, true, true, "PerpendicularEndSecBoundaryMidUp");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_a15, p_e16, p_e36, true, true, true, "PerpendicularEndSecBoundaryRight");

    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_c17, p_c37, true, false, false, "PerpendicularNoSecBoundaryCLeft");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_c15, p_c35, true, true, true, "PerpendicularNoSecBoundaryCMid");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_e165, p_e365, true, true, true, "PerpendicularNoSecBoundaryCMidUp");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_e16, p_e36, true, true, true, "PerpendicularNoSecBoundaryCRight");

    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_b11, p_b31, false, false, false, "PerpendicularNoSecBoundaryBLeft");
    TriangleSegmentIntersection(p_c15, p_c25, p_c35, p_b15, p_b15, p_b35, true, false, true, "PerpendicularNoSecBoundaryBMid");
}


