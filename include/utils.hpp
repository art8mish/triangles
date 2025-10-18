#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace triangles {
const char *LOG_PATH = "logs/triangles.log";

template <std::floating_point T = double> T get_epsilon() {
    if (std::is_same_v<T, double>)
        return 1e-9;
    else if (std::is_same_v<T, long double>)
        return 1e-12L;
    else
        return 1e-6f;
}

// template <std::floating_point T = double> T get_null() {
//     if (std::is_same_v<T, double>)
//         return 0.0;
//     else if (std::is_same_v<T, long double>)
//         return 0.0L;
//     else
//         return 0.0f;
// }

template <std::floating_point T = double>
bool equal(const T &num1, const T &num2, const T &eps) {
    return std::abs(num1 - num2) < eps;
}

template <std::floating_point T = double>
bool is_null(const T &num, const T &eps) {
    return std::abs(num) < eps;
}

template <std::floating_point T = double>
bool is_valid(const T &num) {
    return std::isfinite(num) && !std::isnan(num);
}

// solves system:
// | a1*x + b1*y + c1 = 0
// | a2*x + b2*y + c2 = 0
// returns std::pair(x, y)
template <std::floating_point T = double>
std::pair<T, T> solve_system(const T &a1, const T &b1, const T &c1,
                             const T &a2, const T &b2, const T &c2) {
    T x = std::numeric_limits<T>::quiet_NaN();
    T y = std::numeric_limits<T>::quiet_NaN();

    T det = a1 * b2 - a2 * b1;
    if (!is_null<T>(det)) {
        x = (c2 * b1 - c1 * b2) / det;
        y = (c1 * a2 - c2 * a1) / det;
    }

    return std::pair{x, y};
}

} // namespace triangles