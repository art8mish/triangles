#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <concepts>
#include <limits>
#include <vector>

#include <./utils.hpp>

namespace triangles
{
    
    template<std::floating_point T>
    class Line {
        // L: p_ + t * vec(d_), t - T-variable
        Point p_ {};
        Vector d_ {};

    public:
        Line() = default;
        Line(const Point &p1, const Point &p2) :
            p_ {p1}, d_ {p1, p2} {}

        Line(const T &x1, const T &y1, const T &z1,
             const T &x2, const T &y2, const T &z2) :
            p_ {x1, y1, z1}, d_ {x1, y1, z1, x2, y2, z2} {}

        bool valid() const {


            return std::isnormal(x_) 
                && std::isnormal(y_) 
                && std::isnormal(z_);
        }


        void to_string() const {
            return "Line(" 
            + p_.to_string() + " + "
            + d_.to_string() + "* t)";
        }
    };


    template <typename T>
    class Triangle {
        Point<T> a_ {};
        Point<T> b_ {};
        Point<T> c_ {};

        Triangle(const T &Ax, const T &Ay, const T &Az,
                 const T &Bx, const T &By, const T &Bz,
                 const T &Cx, const T &Cy, const T &Cz) :
            A_{Ax, Ay, Az}, B_{Bx, By, Bz}, C_{Cx, Cy, Cz} {}

    };
} // namespace triangles
