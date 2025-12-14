#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>
#include <stdexcept>

#include "utils.hpp"

namespace triangles {
template <std::floating_point T> class Point {
    T eps_{epsilon<T>()};

public:
    T x;
    T y;
    T z;

    Point(T x, T y, T z) : x{x}, y{y}, z{z} {
    }
    Point(T x, T y) : Point(x, y, 0) {
    }
    
    Point(T x) : Point(x, 0, 0) {
    }

    Point() : Point(0, 0, 0) {}

    void validate() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }

    bool is_valid() const {
        return valid(x) && valid(y) && valid(z);
    }

    static Point<T> get_invalid() {
        return Point<T>{nan<T>(), nan<T>(), nan<T>()};
    }

    static Point<T> get_infinitive() {
        return Point<T>{inf<T>(), inf<T>(), inf<T>()};
    }

    bool is_zero() const {
        return zero<T>(x, eps_) && zero<T>(y, eps_) && zero<T>(z, eps_);
    }

    bool operator==(const Point<T> &rhs) const {
        validate();
        rhs.validate();

        return equal<T>(x, rhs.x, eps_) && equal<T>(y, rhs.y, eps_) &&
               equal<T>(z, rhs.z, eps_);
    }

    bool operator!=(const Point<T> &rhs) const {
        return !(*this == rhs);
    }

    // std::partial_ordering operator<=>(const Point<T>& rhs) const {
    //     if (!is_valid() || !rhs.is_valid())
    //         return std::partial_ordering::unordered;

    //     if (equal<T>(x, rhs.x, eps_) && 
    //         equal<T>(y, rhs.y, eps_) && 
    //         equal<T>(z, rhs.z, eps_)) {
    //         return std::partial_ordering::equivalent;
    //     }

    //     if ((rhs.x - x > eps_) && (rhs.y - y > eps_) && (rhs.z - z > eps_))  return std::partial_ordering::less;
    //     if (x - rhs.x > eps_) && return std::partial_ordering::greater;
    //     if (rhs.y - y > eps_) && return std::partial_ordering::less;
    //     if (y - rhs.y > eps_) && return std::partial_ordering::greater;
    //     if (z + eps_ < rhs.z) && return std::partial_ordering::less;
    //     if (rhs.z + eps_ < z) return std::partial_ordering::greater;
        
    //     return std::partial_ordering::unordered; // Точки "почти равны" но не совсем
    // }

    std::string to_string() const {
        return "Point(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
               std::to_string(z) + ")";
    }
};
} // namespace triangles