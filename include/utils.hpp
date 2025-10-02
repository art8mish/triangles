#pragma once

#include <concepts>
#include <type_traits>

namespace triangles
{
    const char *LOG_PATH = "logs/triangles.log";

    template <std::floating_point T = float>
    T get_epsilon() {
        if (std::is_same_v<T, double>)
            return 1e-9;
        else if (std::is_same_v<T, long double>)
            return 1e-12L;
        else 
            return 1e-6f;
    }

}