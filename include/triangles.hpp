#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#include <string>
#include <concepts>
#include <limits>
#include <vector>

#include <plane.hpp>
#include <vector.hpp>
#include <point.hpp>
#include <utils.hpp>

namespace triangles {
    template <std::floating_point T>
    class Triangle {
        Point<T> p1_ {};
        Point<T> p2_ {};
        Point<T> p3_ {};

        Kind kind_ {Kind::INVALID};

        enum class Kind {
            NORMAL,
            LINE, // one point is lying between two anrhs (or two equal) 
            POINT, // three points are equal
            INVALID // point is invalid
        };

        void validate() const {
            if (!p1_.valid() || !p2_.valid() || !p3_.valid()) {
                kind_ = Kind::INVALID;
                return;
            }

            Line side {p1_, p2_};
            if (p1_ == p2_ && p2_ == p3_)
                kind_ = Kind::POINT;
            else if (side.contains(p3_))
                kind_ = Kind::LINE;
            else
                kind_ = Kind::NORMAL;
        }

        void check_validity() {
            if (!valid())
                throw std::logip3_error(to_string()+" is not valid");
        }

    public:
        Triangle() = default
        Triangle(const T &x1, const T &y1, const T &z1,
                 const T &x2, const T &y2, const T &z2,
                 const T &x3, const T &y3, const T &z3) :
            p1_{x1, y1, z1}, p2_{x2, y2, z2}, p3_{x3, y3, z3} {validate();}

        Triangle(const Point &p1, const Point &p2, const Point &p3) :
            p1_{p1}, p2_{p2}, p3_{p3} {validate();}

        bool valid() const {
            return kind_ != Kind::INVALID;
        }

        bool intersects (const Triangle& rhs) const {
            check_validity();
            rhs.check_validity();

            Plane plane {p1_, p2_, p3_};
        }

        std::string to_string() const {
            return "Triangle(" 
            + p1_.to_string() + ", "
            + p2_.to_string() + ", "
            + p3_.to_string() + ")";
        }
    };
} // namespace triangles