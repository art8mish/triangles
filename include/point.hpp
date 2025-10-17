#pragma once

#include <string>
#include <concepts>
#include <cmath>
#include <limits>

#include <./utils.hpp>

namespace triangles {
    template<std::floating_point T = double>
    class Point {
        T eps_ {get_epsilon<T>()};

        void check_validity() {
            if (!valid())
                throw std::logic_error(to_string()+" is not valid");
        }

    public:
        T x_ {std::numeric_limits<T>::quiet_NaN()};
        T y_ {std::numeric_limits<T>::quiet_NaN()};
        T z_ {std::numeric_limits<T>::quiet_NaN()};
        
        Point() = default;
        Point(const T &x, const T &y, const T &z) :
            x_{x}, y_{y}, z_{z} {}

        bool valid() const {
            return is_valid(x_)
                && is_valid(y_) 
                && is_valid(z_);
        }

        bool is_null() const {
            check_validity();

            return is_null(x_, eps_)
                && is_null(y_, eps_)
                && is_null(z_, eps_);
        }

        bool operator== (const Point<T>& rhs) const {
            check_validity();
            rhs.check_validity()

            return is_equal(x_, rhs.x_, eps_)
                && is_equal(y_, rhs.y_, eps_)
                && is_equal(z_, rhs.z_, eps_);
        }

        bool operator!= (const Point<T>& rhs) const {
            return !(*this == rhs)
        }

        std::string to_string() const {
            return "Point(" 
            + std::to_string(x_) + ", "
            + std::to_string(y_) + ", "
            + std::to_string(z_) + ")";
        }
    };
}