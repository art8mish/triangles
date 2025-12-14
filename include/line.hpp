#pragma once

#include <cmath>
#include <concepts>
#include <stdexcept>
#include <string>
#include <utility>

#include "plane.hpp"
#include "point.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace triangles {
template <std::floating_point T> class Line final {
    T eps_{epsilon<T>()};

    // L: p_ + vec(d_) * t
    Point<T> p_{};
    Vector<T> d_{};

    void validate() const {
        if (!p_.is_valid() || d_.is_zero())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Line(T x1, T y1, T z1, T x2, T y2, T z2) : p_{x1, y1, z1}, d_{x1, y1, z1, x2, y2, z2} {
        validate();
    }

    Line(const Point<T> &p1, const Point<T> &p2) : Line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z) {}

    Line(const Point<T> &p, const Vector<T> &v) : p_{p}, d_{v} {
        validate();
    }

    Line(const Plane<T> &plane1, const Plane<T> &plane2) {
        const Vector<T> &n1 = plane1.normal();
        const Vector<T> &n2 = plane2.normal();

        d_ = n1.ecross(n2);
        if (d_.is_zero()) { // planes are parallel
            throw std::invalid_argument("Can't find intersection line: planes are parallel "
                                        "or coincident");
        }

        // try to find p_ as p_ = a*n1 + b*n2
        // plane: (n, r) + D = 0
        T D1 = plane1.D();
        T D2 = plane2.D();

        T n1_sqr = n1.edot(n1);
        T n2_sqr = n2.edot(n2);
        T n_dot = n1.edot(n2);
        T n_dot_sqr = n_dot * n_dot;

        T denom = n1_sqr * n2_sqr - n_dot_sqr; // > 0
        assert(!zero<T>(denom, eps_));

        T a = (D2 * n_dot - D1 * n2_sqr) / denom;
        T b = (D1 * n_dot - D2 * n1_sqr) / denom;

        p_.x = a * n1.x() + b * n2.x();
        p_.y = a * n1.y() + b * n2.y();
        p_.z = a * n1.z() + b * n2.z();

        validate();
    }

    const Vector<T> &direction() const & {
        return d_;
    }

    const Point<T> &point() const & {
        return p_;
    }

    Point<T> get_point(T t) const {
        return Point<T>{p_.x + d_.x() * t, p_.y + d_.y() * t, p_.z + d_.z() * t};
    }

    bool operator==(const Line<T> &other) const {
        return contains(other.p_) && d_.collinear_with(other.d_);
    }
    bool operator!=(const Line<T> &other) const {
        return !(*this == other);
    }

    bool parallel_to(const Line<T> &other) const {
        return d_.collinear_with(other.d_);
    }

    bool contains(const Point<T> &point) const {
        if (p_ == point)
            return true;
        return d_.collinear_with(Vector<T>{p_, point});
    }

    Point<T> intersection_point(const Plane<T> &plane) const {
        const Vector<T> &n = plane.normal();

        if (n.orthogonal_to(d_)) {
            throw std::invalid_argument(plane.to_string() + " shouldn't be parallel with " +
                                        to_string());
        }

        const Point<T> &line_p = (p_ == plane.point()) ? get_point(1) : p_;
        const Vector<T> v{line_p, plane.point()};

        T t = n.edot(v) / n.edot(d_);
        if (p_ == plane.point())
            t += 1;
        return get_point(t);
    }

    std::string to_string() const {
        return "Line(" + p_.to_string() + " + " + d_.to_string() + "* t)";
    }
};
} // namespace triangles