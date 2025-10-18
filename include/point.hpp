#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>

#include <utils.hpp>

namespace triangles {
template <std::floating_point T> class Point {
    T eps_{get_epsilon<T>()};

    void check_validity() {
        if (!valid())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    T x_ {0};
    T y_ {0};
    T z_ {0};

    Point() = default;
    Point(const T &x, const T &y, const T &z) : x_{x}, y_{y}, z_{z} {}
    Point(const T &x, const T &y) : Point(x, y, 0) {}
    Point(const T &x) : Point(x, 0, 0) {}

    bool valid() const {
        return is_valid(x_) && is_valid(y_) && is_valid(z_);
    }

    bool is_null() const {
        check_validity();

        return is_null(x_, eps_) && is_null(y_, eps_) &&
               is_null(z_, eps_);
    }

    bool operator==(const Point<T> &rhs) const {
        check_validity();
        rhs.check_validity()

                return equal(x_, rhs.x_, eps_) &&
            equal(y_, rhs.y_, eps_) && equal(z_, rhs.z_, eps_);
    }

    bool operator!=(const Point<T> &rhs) const {
        return !(*this == rhs)}

    std::string to_string() const {
        return "Point(" + std::to_string(x_) + ", " +
               std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }
};
} // namespace triangles