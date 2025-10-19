#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>

#include <utils.hpp>

namespace triangles {
template <std::floating_point T> class Point {
    T eps_{get_epsilon<T>()};

public:
    T x_ {0};
    T y_ {0};
    T z_ {0};

    Point() = default;
    Point(const T &x, const T &y, const T &z) : x_{x}, y_{y}, z_{z} {}
    Point(const T &x, const T &y) : Point(x, y, 0) {}
    Point(const T &x) : Point(x, 0, 0) {}

    bool is_valid() const {
        return valid(x_) && valid(y_) && valid(z_);
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    bool is_zero() const {
        check_validity();

        return zero<T>(x_, eps_) && zero<T>(y_, eps_) &&
               zero<T>(z_, eps_);
    }

    bool operator==(const Point<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return equal<T>(x_, rhs.x_, eps_) &&
            equal<T>(y_, rhs.y_, eps_) && equal<T>(z_, rhs.z_, eps_);
    }

    bool operator!=(const Point<T> &rhs) const {
        return !(*this == rhs);
    }

    std::string to_string() const {
        return "Point(" + std::to_string(x_) + ", " +
               std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }
};
} // namespace triangles