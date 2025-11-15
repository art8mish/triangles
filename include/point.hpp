#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>

#include <utils.hpp>

namespace triangles {
template <std::floating_point T> class Point {
    T eps_{epsilon<T>()};

public:
    T x {0};
    T y {0};
    T z {0};

    Point() = default;
    Point(T x, T y, T z) : x{x}, y{y}, z{z} {}
    Point(T x, T y) : Point(x, y, 0) {}
    Point(T x) : Point(x, 0, 0) {}

    bool is_valid() const {
        return valid(x) && valid(y) && valid(z);
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    static Point<T> get_invalid() {
        return Point<T> {nan<T>(), nan<T>(), nan<T>()};
    }

    static Point<T> get_infinitive() {
        return Point<T> {inf<T>(), inf<T>(), inf<T>()};
    }

    bool is_zero() const {
        check_validity();

        return zero<T>(x, eps_) && zero<T>(y, eps_) &&
               zero<T>(z, eps_);
    }

    bool operator==(const Point<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return equal<T>(x, rhs.x, eps_) &&
            equal<T>(y, rhs.y, eps_) && equal<T>(z, rhs.z, eps_);
    }

    bool operator!=(const Point<T> &rhs) const {
        return !(*this == rhs);
    }

    std::string to_string() const {
        return "Point(" + std::to_string(x) + ", " +
               std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};
} // namespace triangles