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
        NORMAL,
        LINE,   // one point is lying between two another (or
                // two equal)
        POINT,  // three points are equal
        INVALID // point is invalid
    };

    Kind kind_{Kind::INVALID};

    void validate() const {
        if (!p1_.is_valid() || !p2_.is_valid() || !p3_.is_valid()) {
            kind_ = Kind::INVALID;
            return;
        }

        Line side{p1_, p2_};
        if (p1_ == p2_ && p2_ == p3_)
            kind_ = Kind::POINT;
        else if (side.contains(p3_))
            kind_ = Kind::LINE;
        else
            kind_ = Kind::NORMAL;
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    // rule: this and other should be in 2d and lie on same plane
    bool normal_projection_intersection_2d_(const Triangle<T> &other) const {
        std::array<Vector<T>, 3> this_normals {
            Vector<T> {-(p2_.y - p1_.y),p2_.x - p1_.x},
            Vector<T> {-(p3_.y - p1_.y), p3_.x - p1_.x},
            Vector<T> {-(p3_.y - p2_.y), p3_.x - p2_.x}
        };

        for (const Vector<T> &n : this_normals) {
            T this_proj1 = n.edot(Vector<T> {p1_});
            T this_proj2 = n.edot(Vector<T> {p2_});
            T this_proj3 = n.edot(Vector<T> {p3_});
            T this_min = std::min({this_proj1, this_proj2, this_proj3});
            T this_max = std::max({this_proj1, this_proj2, this_proj3});

            T other_proj1 = n.edot(Vector<T> {other.p1_});
            T other_proj2 = n.edot(Vector<T> {other.p2_});
            T other_proj3 = n.edot(Vector<T> {other.p3_});
            T other_min = std::min({other_proj1, other_proj2, other_proj3});
            T other_max = std::max({other_proj1, other_proj2, other_proj3});

            if (this_max < other_min || other_max < this_min) 
                return false;
        }
        return true;
    }

    // rule: this and other lie on same plane
    bool intersects_2d_(const Triangle<T> &other) const {
        const Plane<T> &plane = get_plane();
        assert(plane == other.get_plane());

        const Vector<T> &plane_n = plane.normal();
        const Point<T> &plane_p = plane.point();
        Vector<T> u = plane_n.get_perpendicular();
        Vector<T> v = plane_n.ecross(u);

        Triangle<T> this_2d = to_2d(u, v, plane_p);
        assert(this_2d.is_valid());

        Triangle<T> other_2d = other.to_2d(u, v, plane_p);
        assert(other_2d.is_valid());

        if (!this_2d.normal_projection_intersection_2d_(other_2d))
            return false;
        if (!other_2d.normal_projection_intersection_2d_(this_2d))
            return false;
        return true;
    }

    // rule: u orthogonal to v (2d basis with p)
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
        T dist1 = plane.signed_distance(p1_);
        if (zero<T>(dist1))
            return true;

        T dist2 = plane.signed_distance(p2_);
        if ((zero<T>(dist2)) || (dist1 * dist2 < 0))
            return true;

        T dist3 = plane.signed_distance(p3_);
        if ((zero<T>(dist3)) || (dist2 * dist3 < 0))
            return true;

        return false;
    }

    // return t for line equation p + vec(d) * t of Line(p2, p1) intersection point
    T line_intersection_point_(const Line<T> &line,
                               const Point<T> &p1, const T &sdist1,
                               const Point<T> &p2, const T &sdist2) {

        const Vector<T> &line_dir = line.direction();
        const Point<T> &line_p = line.point();

        T proj1 = line_dir.edot(Vector{line_p, p1});
        if (zero<T>(sdist1))
            return proj1;

        T proj2 = line_dir.edot(Vector{line_p, p2});
        if (zero<T>(sdist2))
            return proj2;
        if (sdist1 * sdist2 > 0)
            return nan<T>();

        return proj1 + (proj2 - proj1) * sdist1 / (sdist1 - sdist2);
    }

    // rule: triangle intersects line and plane, line is lying on plane
    std::pair<T, T> line_intersection_(const Line<T> &line, const Plane<T> &plane) const {
        T sdist1 = plane.signed_distance(p1_);
        T sdist2 = plane.signed_distance(p2_);
        T sdist3 = plane.signed_distance(p3_);

        T t0 = line_intersection_point_(line, p1_, sdist1, p2_, sdist2);
        T t1 = line_intersection_point_(line, p1_, sdist1, p3_, sdist3);
        if (!valid(t0))
            t0 = line_intersection_point_(line, p2_, sdist2, p3_, sdist3);
        else if (!valid(t1))
            t1 = line_intersection_point_(line, p2_, sdist2, p3_, sdist3);
        assert(valid(t0) && valid(t1));
        return std::pair<T, T>{t0, t1}; // can be the same
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

    // TODO: optimize to count dist once
    bool intersects(const Triangle<T> &other) const {
        check_validity();
        other.check_validity();

        Plane<T> this_plane = get_plane();
        assert(this_plane.is_valid());

        if (!other.intersects_plane_(this_plane))
            return false;

        Plane<T> other_plane = other.get_plane();
        assert(other_plane.is_valid());

        if (this_plane == other_plane)
            return intersects_2d_(other);
        
        if (!intersects_plane_(other_plane))
            return false;

        Line<T> common_line {this_plane, other_plane};
        assert(common_line.is_valid());

        std::pair<T, T> this_t = line_intersection_(common_line, other_plane);
        std::pair<T, T> other_t = other.line_intersection_(common_line, this_plane);

        T a = std::max(
            std::min(this_t.first, this_t.second),
            std::min(other_t.first, other_t.second)
        );

        T b = std::min(
            std::max(this_t.first, this_t.second), 
            std::max(other_t.first, other_t.second)
        );

        return equal<T>(a, b, eps_) || (a < b);
    }

    Plane<T> get_plane() const {
        return Plane<T>{p1_, p2_, p3_};
    }

    std::string to_string() const {
        return "Triangle(" + p1_.to_string() + ", " +
               p2_.to_string() + ", " + p3_.to_string() + ")";
    }
};
} // namespace triangles