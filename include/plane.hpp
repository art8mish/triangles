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
        if (p_.is_valid() && n_.is_valid() && !n_.is_zero())
            validity_ = true;
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Plane(const Point<T> &p, const Vector<T> &n) : p_{p}, n_{n} {
        validate();
    }

    Plane(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3)
        : Plane(p1, Vector<T>{p1, p2}.ecross(Vector<T>{p1, p3}).normalize()) {}

    bool is_valid() const {
        return validity_;
    }

    const Vector<T>& normal() const & {
        return n_;
    }

    const Point<T>& point() const & {
        return p_;
    }

    bool operator==(const Plane<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return contains(rhs.p_) && parallel_to(rhs);
    }

    bool operator!=(const Plane<T> &rhs) const {
        return !(*this == rhs);
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

        return n_.edot(Vector{p_, point});
    }

    // L: (n_, r) + D = 0
    T D() const {
        check_validity();
        return -n_.edot(p_);
    }

    bool parallel_to(const Plane<T> &other) const {
        check_validity();
        other.check_validity();

        return n_.collinear_with(other.n_);
    }

    std::pair<Vector<T>, Vector<T>> get_basis_vectors() const {
        check_validity();

        Vector<T> u = n_.get_perpendicular();
        Vector<T> v = n_.ecross(u);
        return std::pair<Vector<T>, Vector<T>>{u, v};
    }

    std::string to_string() const {
        return "Plane((" + n_.to_string() + ", (x, y, z) -" +
               p_.to_string() + ") = 0";
    }
};
} // namespace triangles