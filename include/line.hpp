#pragma once

#include <string>
#include <concepts>
#include <cmath>
#include <stdexcept>

#include <./point.hpp>
#include <./utils.hpp>

namespace triangles {
    template<std::floating_point T>
    class Line {
        // L: p_ + vec(d_) * t
        Point p_ {};
        Vector d_ {};

        bool validity_ {false};
        void validate() {
            if (p_.valid() && d_.valid() && !d_.is_null())
                validity_ = true;
        }

        void check_validity() {
            if (!valid())
                throw std::logic_error(to_string()+" is not valid");
        }

    public:
        Line() = default;
        Line(const Point<T> &p1, const Point<T> &p2) : 
            p_ {p1}, d_ {p1, p2} {validate()}

        Line(const Point<T> &p, const Vector<T> &v) : 
            p_ {p}, d_ {v} {validate()}

        Line(const T &x1, const T &y1, const T &z1,
             const T &x2, const T &y2, const T &z2) :
            p_ {x1, y1, z1}, d_ {x1, y1, z1, x2, y2, z2} {validate()}

        bool valid() const {
            return validity_;
        }

        bool operator== (const Line<T>& other) const {
            check_validity();
            other.check_validity();

            return contains(other.p_)
                && d_.collinear_with(other.d_);
        }
        bool operator!= (const Line<T>& other) const {
            return !(*this == other)
        }
        
        bool parallel_to (const Line<T>& other) const {
            check_validity();
            other.check_validity();

            return d_.collinear_with(other.d_);
        }

        bool contains (const Point<T>& point) const {
            check_validity();
            point.check_validity();

            if (p_ == point)
                return true;

            Vector point_vec {p_, point};
            return d_.collinear_with(point_vec);
        }

        std::string to_string() const {
            return "Line(" 
            + p_.to_string() + " + "
            + d_.to_string() + "* t)";
        }
    };
}