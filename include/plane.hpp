#pragma once

#include <cmath>
#include <concepts>
#include <stdexcept>
#include <string>

#include <point.hpp>
#include <utils.hpp>
#include <vector.hpp>

namespace triangles {
template <std::floating_point T> class Plane {
    // L: (n_, r - p_) = 0

    Point<T> p_{};
    Vector<T> n_{};

    bool validity_{false};
    void validate() {
        if (p_.valid() && n_.valid() && !n_.is_null())
            validity_ = true;
    }

    void check_validity() {
        if (!valid())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Plane() = default;
    Plane(const Point<T> &p, const Vector<T> &n) : p_{p}, n_{n} {
        validate();
    }

    Plane(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3)
        : p_{p1}, n_{Vector<T>{p1, p2}.ecross(Vector<T>{p1, p3})} {
        validate();
    }

    bool valid() const {
        return validity_;
    }

    const Vector<T> &normal() return n_;

    bool operator==(const Plane<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return contains(rhs.p_) && parallel_to(rhs);
    }

    bool operator!=(const Plane<T> &rhs) const {
        return !(*this == rhs)
    }

    bool contains(const Point<T> &point) const {
        check_validity();
        point.check_validity();

        if (p_ == point)
            return true;
        return n_.orthogonal_to(Vector<T>{p_, point});
    }

    T signed_distance(const Point<T> &point) const {
        check_validity();
        point.check_validity();

        return n_.edot(Vector{plane.p_, point});
    }

    // L: (n_, r) + D = 0
    T D() const {
        check_validity();
        return -n_.edot(p_);
    }

    bool parallel_to(const Plane<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return n_.collinear_with(rhs.n_)
    }

    std::string to_string() const {
        return "Plane((" + n_.to_string() + ", (x, y, z) -" +
               p_.to_string() + ") = 0";
    }
};
} // namespace triangles