#pragma once

#include <concepts>
#include <type_traits>

namespace triangles
{
    const char *LOG_PATH = "logs/triangles.log";

    template <std::floating_point T = double>
    T get_epsilon() {
        if (std::is_same_v<T, double>)
            return 1e-9;
        else if (std::is_same_v<T, long double>)
            return 1e-12L;
        else 
            return 1e-6f;
    }

    template <std::floating_point T = double>
    T get_null() {
        if (std::is_same_v<T, double>)
            return 0.0;
        else if (std::is_same_v<T, long double>)
            return 0.0L;
        else 
            return 0.0f;
    }

    template <std::floating_point T = double>
    bool is_equal(const T& num1, const T& num2, const T& eps) {
        return std::abs(num1 - num2) < eps;
    }

    template <std::floating_point T = double>
    bool is_null(const T& num,const T& eps) {
        return std::abs(num) < eps;
    }

    template <std::floating_point T = double>
    bool is_valid(T num) {
        return std::isfinite(num) && !std::isnan(num);
    }

}