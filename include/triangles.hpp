#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <concepts>
#include <limits>
#include <string>
#include <vector>

#include <line.hpp>
#include <plane.hpp>
#include <point.hpp>
#include <utils.hpp>
#include <vector.hpp>

namespace triangles {
template <std::floating_point T> class Triangle {
    Point<T> p1_{};
    Point<T> p2_{};
    Point<T> p3_{};
    T eps_{epsilon<T>()};

    enum class Kind {
        TRIANLE,
        SEGMENT, // one point is lying between two another (or
                 // two equal), after validation:
                 // line_ should be initialized
        POINT,   // three points are equal
        INVALID  // point is invalid
    };

    Kind kind_{Kind::INVALID};

    void validate() const {
        if (!p1_.is_valid() || !p2_.is_valid() || !p3_.is_valid()) {
            kind_ = Kind::INVALID;
            return;
        }

        if (p1_ == p2_) {
            if (p2_ == p3_)
                kind_ = Kind::POINT;
            else
                kind_ = Kind::SEGMENT;
        }
        else {
            Line side{p1_, p2_};
            if (side.contains(p3_))
                kind_ = Kind::SEGMENT;
            else
                kind_ = Kind::TRIANGLE;
        }
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    // rule: this should be in 2d
    std::array<Vector<T>, 3> get_2d_normals_() const {
        return std::array<Vector<T>, 3> {
            Vector<T> {-(p2_.y - p1_.y), p2_.x - p1_.x},
            Vector<T> {-(p3_.y - p1_.y), p3_.x - p1_.x},
            Vector<T> {-(p3_.y - p2_.y), p3_.x - p2_.x}
        };
    }

    T projection (const Vector<T>& axis, const Point<T>& point) {
        return axis.edot(Vector<T> {point});
    }

    std::pair<T, T> get_projection_segment_ (const Vector<T>& axis) {
        T proj1 = projection(axis, p1_);
        T proj2 = projection(axis, p2_);
        T proj3 = projection(axis, p3_);

        return std::pair<T, T> {
            std::min({proj1, proj2, proj3}), 
            std::max({proj1, proj2, proj3});
        };
    }

    static bool segments_intersect_(T segment1_a, T segment1_b, T segment2_a, T segment2_b) const {
        const T max_a = std::max(segment1_a, segment2_a);
        const T min_b = std::min(segment1_b, segment2_b);

        return (max_a < min_b) || equal<T>(max_a, min_b, eps_);
    }

    // rule: this and other should be in 2d and lie on same plane
    bool triangle_normal_proj_intersection_2d_(const Triangle<T> &other) const {
        const auto normals =  get_2d_normals_();
        for (auto &n : normals) {
            const auto [this_a, this_b] = get_projection_segment_(n);
            const auto [other_a, other_b] = other.get_projection_segment_(n);
            if (!segments_intersect_(this_a, this_b, other_a, other_b))
                return false;
        }
        return true;
    }

    // rule: this and other lie on same plane
    bool triangle_triangle_intersection_2d_(const Triangle<T> &other) const {
        const Plane<T> &plane = get_plane();
        assert(plane == other.get_plane());

        const auto [u, v] = plane.get_basis_vectors();

        const Triangle<T> this_2d = to_2d_(u, v, plane.point());
        assert(this_2d.is_valid());

        const Triangle<T> other_2d = other.to_2d_(u, v, plane.point());
        assert(other_2d.is_valid());

        if (!this_2d.triangle_normal_proj_intersection_2d_(other_2d))
            return false;
        if (!other_2d.triangle_normal_proj_intersection_2d_(this_2d))
            return false;
        return true;
    }

    Triangle<T> to_2d_(const Vector<T> &u, const Vector<T> &v, const Point<T> &p) {
        return Triangle <T>{
            Point<T> {
                u.edot(Vector<T> {p, p1_}),
                v.edot(Vector<T> {p, p1_})
            },
            Point<T> {
                u.edot(Vector<T> {p, p2_}),
                v.edot(Vector<T> {p, p2_})
            },
            Point<T> {
                u.edot(Vector<T> {p, p3_}),
                v.edot(Vector<T> {p, p3_})
            },
        };
    }

    bool intersects_plane_(const Plane<T> &plane) const {
        const T dist1 = plane.signed_distance(p1_);
        if (zero<T>(dist1, eps_))
            return true;

        const T dist2 = plane.signed_distance(p2_);
        if ((zero<T>(dist2, eps_)) || (dist1 * dist2 < 0))
            return true;

        const T dist3 = plane.signed_distance(p3_);
        if ((zero<T>(dist3, eps_)) || (dist2 * dist3 < 0))
            return true;

        return false;
    }

    // return t for line equation p + vec(d) * t of Line(p2, p1) intersection point
    T line_intersection_point_(const Line<T> &line,
                               const Point<T> &p1, const T &sdist1,
                               const Point<T> &p2, const T &sdist2) {

        const Vector<T> &line_dir = line.direction();
        const Point<T> &line_p = line.point();

        const T proj1 = line_dir.edot(Vector{line_p, p1});
        if (zero<T>(sdist1, eps_))    
            return proj1;

        const T proj2 = line_dir.edot(Vector{line_p, p2});
        if (zero<T>(sdist2, eps_))
            return proj2;
        if (sdist1 * sdist2 > 0)
            return nan<T>();

        return proj1 + (proj2 - proj1) * sdist1 / (sdist1 - sdist2);
    }

    // rule: triangle intersects plane on line
    std::pair<T, T> triangle_line_intersection_segment_ (const Line<T> &line, const Plane<T> &plane) const {
        const T sdist1 = plane.signed_distance(p1_);
        const T sdist2 = plane.signed_distance(p2_);
        const T sdist3 = plane.signed_distance(p3_);

        T t0 = line_intersection_point_(line, p1_, sdist1, p2_, sdist2);
        T t1 = line_intersection_point_(line, p1_, sdist1, p3_, sdist3);
        if (!valid(t0))
            t0 = line_intersection_point_(line, p2_, sdist2, p3_, sdist3);
        else if (!valid(t1))
            t1 = line_intersection_point_(line, p2_, sdist2, p3_, sdist3);
        assert(valid(t0) && valid(t1));
        return std::pair<T, T>{std::min(t0, t1), std::max(t0, t1)}; // can be the same
    }

    bool triangle_triangle_intersection_(const Triangle<T> &other) const {
        assert(kind_ == Kind::TRIANLE && other.kind_ == Kind::TRIANLE);

        const Plane<T> this_plane = get_plane();
        assert(this_plane.is_valid());

        if (!other.intersects_plane_(this_plane))
            return false;

        const Plane<T> other_plane = other.get_plane();
        assert(other_plane.is_valid());

        if (this_plane == other_plane)
            return triangle_triangle_intersection_2d_(other);
        
        if (!intersects_plane_(other_plane))
            return false;

        const Line<T> common_line {this_plane, other_plane};
        assert(common_line.is_valid());

        const auto [this_a, this_b] = triangle_line_intersection_segment_(common_line, other_plane);
        const auto [other_a, other_b] = other.triangle_line_intersection_segment_(common_line, this_plane);

        return segments_intersect_(this_a, this_b, other_a, other_b)
    }

    // barycentric coordinates
    bool triangle_point_intersection_(const Point<T> &point) const {
        assert(kind_ == Kind::TRIANGLE);

        Plane<T> plane = get_plane();
        assert(plane.is_valid());

        if (!plane.contains(point))
            return false;

        // vec(P) = vec(p1) + a * vec(p1, p2) + b * vec(p1, p3) 
        // |_w                    |_u               |_v
        // a >= 0, b >= 0, a + b <= 1
        Vector<T> u = Vector<T>{p1_, p2_};
        Vector<T> v = Vector<T>{p1_, p3_};
        Vector<T> w = Vector<T>{p1_, point};

        // solve system:
        // { (w, v) = a * (u, v) + b * (v, v) | (wv = a * uv + b * vv)
        // { (w, u) = a * (u, u) + b * (v, u) | (wu = a * uu + b * uv)

        T uu = u.edot(u);
        T uv = u.edot(v);
        T vv = v.edot(v);
        T wu = w.edot(u);
        T wv = w.edot(v);

        T det = uu * vv - uv * uv;
        assert(!zero(det, eps_));
        T rev_det = 1 / det;

        T a = (wu * vv - wv * uv) * rev_det;
        T b = (wv * uu - wu * uv) * rev_det;
        T c = 1 - a - b;
        return (zero(a, eps_) || a > 0) 
            && (zero(b, eps_) || b > 0) 
            && (zero(c, eps_) || c > 0);
    }


    //rule: triangle and segment is lying on same plane
    bool triangle_segment_intersection_2d_(const Triangle<T> &other) const {
        assert(kind_ == Kind::TRIANLE && other.kind_ == Kind::SEGMENT);

        Plane<T> plane = get_plane();
        const auto [u, v] = plane.get_basis_vectors();

        const Triangle<T> this_2d = to_2d_(u, v, plane.point());
        assert(this_2d.is_valid());

        const Triangle<T> other_2d = other.to_2d_(u, v, plane.point());
        assert(other_2d.is_valid());

        return this_2d.triangle_normal_proj_intersection_2d_(other_2d);
    }

    bool triangle_segment_intersection_(const Triangle<T> &other) const {
        assert(kind_ == Kind::TRIANGLE && other.kind_ == Kind::SEGMENT);

        Plane<T> plane = get_plane();
        assert(plane.is_valid());

        const Line<T> line = other.to_line();
        const Vector<T> &d = line.direction();

        assert(line.is_valid());
        if (plane.normal().orthogonal_to(line.direction())) {
            if (!plane.contains(line.point()))
                return false;

            return triangle_segment_intersection_2d_(other);
        }
        Point<T> intersection_p = plane_line_intersection_point_(plane, line);
        if (!other.segment_point_intersection_(intersection_p))
            return false;

        return triangle_point_intersection_(intersection_p);
    }

    //rule: triangle is segment
    const Line<T> to_line() const {
        assert(kind_ == Kind::SEGMENT);
        return (p1_ != p2_) ? Line<T>{p1_, p2_} : Line<T>{p1_, p3_};
    }

    // rule: plane and line is not parallel
    static Point<T> plane_line_intersection_point_(const Plane<T> plane, Line<T> &line) {
        const Vector<T> &n = plane.normal();
        const Vector<T> &d = line.direction();

        assert(!n.orthogonal_to(d));
        T t = n.edot(Vector<T> {plane.point(), line.point()}) / n.edot(d);
        return line.get_point(t);
    }


    bool segment_point_intersection_(const Point<T> &point) const {
        assert(kind_ == Kind::SEGMENT);

        const Line<T> line = to_line();
        if (!line.contains(point))
            return false;

        const auto [a, b] = get_projection_segment_(line.direction());
        T proj = projection(axis, point);
        return proj > (a - eps_) && proj < (b + eps_);
    }

    bool segment_segment_intersection_(const Triangle<T> &other) const {
        assert(kind_ == Kind::SEGMENT);
        assert(other.kind_ == Kind::SEGMENT);

        const Line<T> line1 = to_line();
        const Vector<T> &d1 = line1.direction();

        const Line<T> line2 = other.to_line();
        const Vector<T> &d2 = line2.direction();

        if (d1.is_parallel(d2))
            return line1.contains(line2.point());

        const Vector<T> point_vec {this_line.point(), other_line.point()};

        const T scalar_triple_prod = d1.edot(d2.ecross(point_vec));
        if (!zero(scalar_triple_prod, eps_))
            return false

        // L1: q1 = vec(p1) + t1 * d1
        // L2: q2 = vec(p2) + t2 * d2
        // minimizing distance vector d = q2 - q1 = vec(p1, p2) + t2 * d2 - t1 * d1
        // (d, d1) = 0 && (d, d2) = 0 (minimum d is perpendicular to d1 and d2)
        // solve system (u = point_vec = vec(p1, p2))
        // { (u, d1) = t1 * (d1, d1) - t2 * (d1, d2) | u1 = t1 * d11 - t2 * d12
        // { (u, d2) = t1 * (d1, d2) - t2 * (d2, d2) | u2 = t1 * d12 - t2 * d22

        T u1 = point_vec.edot(d1);
        T u2 = point_vec.edot(d2);
        T d11 = d1.edot(d1);
        T d22 = d2.edot(d2);
        T d12 = d1.edot(d2);

        T det = d11 * d22 - d12 * d12;
        assert(!zero(det, eps_))
        T t1 = (u1 * d22 - u2 * d12) / det;
        T t2 = (u1 * d12 - u2 * d11) / det;

        const Point<T> q1 = line1.get_point(t1);
        if (!segment_point_intersection_(q1))
            return false;

        const Point<T> q2 = line2.get_point(t2);
        if (!other.segment_point_intersection_(q2))
            return false;

        const Vector<T> d {q1, q2};
        return d.is_zero();
    }

public:
    Triangle() = default;
    Triangle(const T &x1, const T &y1, const T &z1, const T &x2,
             const T &y2, const T &z2, const T &x3, const T &y3,
             const T &z3)
        : p1_{x1, y1, z1}, p2_{x2, y2, z2}, p3_{x3, y3, z3} {
        validate();
    }

    Triangle(const Point<T> &p1, const Point<T> &p2,
             const Point<T> &p3)
        : p1_{p1}, p2_{p2}, p3_{p3} {
        validate();
    }

    bool is_valid() const {
        return kind_ != Kind::INVALID;
    }


    bool intersects(const Triangle<T> &other) const {
        check_validity();
        other.check_validity();

        if (kind_ == Kind::POINT) {
            if (other.kind_ == Kind::POINT)
                return other.p1_ == p1_;
    
            else if (other.kind_ == Kind::SEGMENT)
                return other.segment_point_intersection_(p1_);

            return other.triangle_point_intersection_(p1_);
        }

        else if (kind_ == Kind::SEGMENT) {
            if (other.kind_ == Kind::POINT)
                return segment_point_intersection_(other.p1_);

            else if (other.kind__ == Kind::SEGMENT)
                return segment_segment_intersection_(other.p1_);

            return other.triangle_segment_intersection_(*this);
        }

        // triangle
        if (other.kind_ == Kind::POINT)
            return other.triangle_point_intersection_(other.p1_);
    
        else if (other.kind__ == Kind::SEGMENT)
            triangle_segment_intersection_(other);

        return triangle_triangle_intersection_(other);    
    }
    

    Plane<T> get_plane() const {
        return Plane<T>{p1_, p2_, p3_};
    }

    std::string to_string() const {
        return "Triangle(" + p1_.to_string() + ", " +
               p2_.to_string() + ", " + p3_.to_string() + ")";
    }
};
}; // namespace triangles