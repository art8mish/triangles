#pragma once

#include <cmath>
#include <concepts>
#include <stdexcept>
#include <string>
#include <utility>

#include <plane.hpp>
#include <point.hpp>
#include <utils.hpp>
#include <vector.hpp>

namespace triangles {
template <std::floating_point T> class Line {
    T eps_{epsilon<T>()};

    // L: p_ + vec(d_) * t
    Point<T> p_{};
    Vector<T> d_{};

    bool validity_{false};
    void validate() {
        if (p_.is_valid() && d_.is_valid() && !d_.is_zero())
            validity_ = true;
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Line(const T &x1, const T &y1, const T &z1, const T &x2,
         const T &y2, const T &z2)
        : p_{x1, y1, z1}, d_{x1, y1, z1, x2, y2, z2} {
        validate();
    }

    Line(const Point<T> &p1, const Point<T> &p2)
        : Line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z) {}

    Line(const Point<T> &p, const Vector<T> &v) : p_{p}, d_{v} {
        validate();
    }

    Line(const Plane<T> &plane1, const Plane<T> &plane2) {
        const Vector<T> &n1 = plane1.normal();
        const Vector<T> &n2 = plane2.normal();

        d_ = n1.ecross(n2);
        if (d_.is_zero()) { // planes are parallel
            validate();
            throw std::logic_error(
                "Can't find intersection line: planes are parallel "
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

    bool is_valid() const {
        return validity_;
    }

    const Vector<T> &direction() const & {
        check_validity();
        return d_;
    }
    
    const Point<T> &point() const & {
        check_validity();
        return p_;
    }

    Point<T> get_point(T t) {
        check_validity();
        return Point<T> {
            p_.x + d_.dx_ * t,  
            p_.y + d_.dy_ * t,
            p_.z + d_.dz_ * t
        };
    }

    bool operator==(const Line<T> &other) const {
        check_validity();
        other.check_validity();

        return contains(other.p_) && d_.collinear_with(other.d_);
    }
    bool operator!=(const Line<T> &other) const {
        return !(*this == other);
    }

    bool parallel_to(const Line<T> &other) const {
        check_validity();
        other.check_validity();

        return d_.collinear_with(other.d_);
    }

    bool contains(const Point<T> &point) const {
        check_validity();
        point.check_validity();

        if (p_ == point)
            return true;
        return d_.collinear_with(Vector<T>{p_, point});
    }

    std::string to_string() const {
        return "Line(" + p_.to_string() + " + " + d_.to_string() +
               "* t)";
    }
};
} // namespace triangles