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
    T eps_{get_epsilon<T>()};

    Kind kind_{Kind::INVALID};

    enum class Kind {
        NORMAL,
        LINE,   // one point is lying between two anrhs (or
                // two equal)
        POINT,  // three points are equal
        INVALID // point is invalid
    };

    void validate() const {
        if (!p1_.valid() || !p2_.valid() || !p3_.valid()) {
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

    void check_validity() {
        if (!valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    // rule: lhs and rhs lie on plane
    bool intersects_2d_(const Triangle<T> &rhs) const {
        const Plane<T> &plane = get_plane();
        assert(plane == rhs.get_plane());

        const Vector<T> &plane_n = plane.normal();
        const Point<T> &plane_p = plane.point();
        Vector<T> u = plane_n.get_perpendicular();
        Vector<T> v = plane_n.ecross(u);

        Triangle<T> lhs = to_2d(u, v, plane_p);
        Triangle<T> rhs = rhs.to_2d(u, v, plane_p);

        std::array<Vector<T>, 3> lhs_normals {
            Vector<T> {
                -(lhs.p2_.y_ - lhs.p1_.y_),
                lhs.p2_.x_ - lhs.p1_.x_
            },
            Vector<T> {
                -(lhs.p3_.y_ - lhs.p1_.y_),
                lhs.p3_.x_ - lhs.p1_.x_
            },
            Vector<T> {
                -(lhs.p3_.y_ - lhs.p2_.y_),
                lhs.p3_.x_ - lhs.p2_.x_
            }
        };

        for (const Vector<T> &n : lhs_normals) {
            T lhs_proj1 = n.edot(Vector<T> {lhs.p1_});
            T lhs_proj2 = n.edot(Vector<T> {lhs.p2_});
            T lhs_proj3 = n.edot(Vector<T> {lhs.p3_});
            T lhs_min = std::min({lhs_proj1, lhs_proj2, lhs_proj3});
            T lhs_max = std::max({lhs_proj1, lhs_proj2, lhs_proj3});

            T rhs_proj1 = n.edot(Vector<T> {lhs.p1_});
            T rhs_proj2 = n.edot(Vector<T> {lhs.p2_});
            T rhs_proj3 = n.edot(Vector<T> {lhs.p3_});
            T rhs_min = std::min({rhs_proj1, rhs_proj2, rhs_proj3});
            T rhs_max = std::max({rhs_proj1, rhs_proj2, rhs_proj3});

            if (lhs_max < rhs_min || rhs_max < lhs_min) 
                return false;
        }

        // std::array<Vector<T>, 3> rhs_normals {
        //     Vector<T> {
        //         -(lhs.p2_.y_ - lhs.p1_.y_),
        //         lhs.p2_.x_ - lhs.p1_.x_
        //     },
        //     Vector<T> {
        //         -(lhs.p3_.y_ - lhs.p1_.y_),
        //         lhs.p3_.x_ - lhs.p1_.x_
        //     },
        //     Vector<T> {
        //         -(lhs.p3_.y_ - lhs.p2_.y_),
        //         lhs.p3_.x_ - lhs.p2_.x_
        //     }
        // };

        // for (const Vector<T> &n : normals) {
        //     T lhs_proj1 = n.edot(Vector<T> {lhs.p1_});
        //     T lhs_proj2 = n.edot(Vector<T> {lhs.p2_});
        //     T lhs_proj3 = n.edot(Vector<T> {lhs.p3_});
        //     T lhs_min = std::min({lhs_proj1, lhs_proj2, lhs_proj3});
        //     T lhs_max = std::max({lhs_proj1, lhs_proj2, lhs_proj3});

        //     T rhs_proj1 = n.edot(Vector<T> {lhs.p1_});
        //     T rhs_proj2 = n.edot(Vector<T> {lhs.p2_});
        //     T rhs_proj3 = n.edot(Vector<T> {lhs.p3_});
        //     T rhs_min = std::min({rhs_proj1, rhs_proj2, rhs_proj3});
        //     T rhs_max = std::max({rhs_proj1, rhs_proj2, rhs_proj3});

        //     if (lhs_max < rhs_min || rhs_max < lhs_min) std::array<Vector<T>, 3> rhs_normals {
        //     Vector<T> {
        //         -(lhs.p2_.y_ - lhs.p1_.y_),
        //         lhs.p2_.x_ - lhs.p1_.x_
        //     },
        //     Vector<T> {
        //         -(lhs.p3_.y_ - lhs.p1_.y_),
        //         lhs.p3_.x_ - lhs.p1_.x_
        //     },
        //     Vector<T> {
        //         -(lhs.p3_.y_ - lhs.p2_.y_),
        //         lhs.p3_.x_ - lhs.p2_.x_
        //     }
        // };

        // for (const Vector<T> &n : normals) {
        //     T lhs_proj1 = n.edot(Vector<T> {lhs.p1_});
        //     T lhs_proj2 = n.edot(Vector<T> {lhs.p2_});
        //     T lhs_proj3 = n.edot(Vector<T> {lhs.p3_});
        //     T lhs_min = std::min({lhs_proj1, lhs_proj2, lhs_proj3});
        //     T lhs_max = std::max({lhs_proj1, lhs_proj2, lhs_proj3});

        //     T rhs_proj1 = n.edot(Vector<T> {lhs.p1_});
        //     T rhs_proj2 = n.edot(Vector<T> {lhs.p2_});
        //     T rhs_proj3 = n.edot(Vector<T> {lhs.p3_});
        //     T rhs_min = std::min({rhs_proj1, rhs_proj2, rhs_proj3});
        //     T rhs_max = std::max({rhs_proj1, rhs_proj2, rhs_proj3});

        //     if (lhs_max < rhs_min || rhs_max < lhs_min) 
        //         return false;
        // }
        //         return false;
        // }
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
        if (is_null(dist1))
            return true;

        T dist2 = plane.signed_distance(p2_);
        if ((is_null(dist2)) || (dist1 * dist2 < 0))
            return true;

        T dist3 = plane.signed_distance(p3_);
        if ((is_null(dist3)) || (dist2 * dist3 < 0))
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
        if is_null(sdist1)
            return proj1;

        T proj2 = line_dir.edot(Vector{line_p, p2});
        if is_null(sdist2)
            return proj2;
        if (sdist1 * sdist2 > 0)
            return std::numeric_limits<T>::quiet_NaN();

        return proj1 + (proj2 - proj1) * sdist1 / (sdist1 - sdist2);
    }

    // rule: triangle intersects line and plane, line is lying on plane
    std::pair<T, T> line_intersection_(const Line<T> &line, const Plane<T> &plane) const {
        T sdist1 = plane.signed_distance(p1_);
        T sdist2 = plane.signed_distance(p2_);
        T sdist3 = plane.signed_distance(p3_);

        T t0 = line_intersection_point_(line, p1_, sdist1, p2_ sdist2);
        T t1 = line_intersection_point_(line, p1_, sdist1, p3_ sdist3);
        if (!is_valid(t0))
            t0 = line_intersection_point_(line, p2_, sdist2, p3_ sdist3);
        else if (!is_valid(t1))
            t1 = line_intersection_point_(line, p2_, sdist2,
                                          p3_ sdist3);
        assert(is_valid(t0) && is_valid(t1));
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

    bool valid() const {
        return kind_ != Kind::INVALID;
    }

    // TODO: optimize to count dist once
    bool intersects(const Triangle<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        Plane<T> lhs_plane = get_plane();
        if (!rhs.intersects_plane_(lhs_plane))
            return false;

        Plane<T> rhs_plane = rhs.get_plane();
        if (lhs_plane == rhs_plane)
            return intersects_2d_(rhs);
        
        if (!intersects_plane_(rhs_plane))
            return false;

        Line<T> common_line {lhs_plane, rhs_plane};
        std::pair<T, T> lhs_t = line_intersection_(common_line, rhs_plane);
        std::pair<T, T> rhs_t = rhs.line_intersection_(common_line, lhs_plane);
        T a = std::min(lhs_t.first, lhs_t.second);
        T t1 = t.second;

        T a = std::max(
            std::min(lhs_t.first, lhs_t.second),
            std::min(rhs_t.first, rhs_t.second),
        );

        T b = std::min(
            std::max(lhs_t.first, lhs_t.second), 
            std::max(lhs_t.first, lhs_t.second), 
        );

        return is_equal(a, b, eps_) || (a < b);
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