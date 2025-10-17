#pragma once

#include <string>
#include <concepts>
#include <cmath>
#include <stdexcept>

#include <vector.hpp>
#include <utils.hpp>
namespace triangles {
    template<std::floating_point T>
    class Plane {
        // L: p_ + vec(d_) * t
        
        Point p_ {};
        Vector n_ {};
        
        bool validity_ {false};
        void validate() {
            if (p_.valid() && n_.valid() && !n_.is_null())
                validity_ = true;
        }

        void check_validity() {
            if (!valid())
                throw std::logic_error(to_string()+" is not valid");
        }

    public:
        Plane() = default;
        Plane(const Point<T> &p, const Vector<T> &n) : 
            p_ {p}, n_ {n} {validate();}

        Plane(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) :
            p_ {p1}, n_{Vector{p1, p2}.ecross(Vector{p1, p3})} {validate();}

        bool valid() const {
            return validity_;
        }

        bool operator== (const Plane<T>& rhs) const {
            check_validity();
            rhs.check_validity();

            return contains(rhs.p_) && parallel_to(rhs);
        }

        bool operator!= (const Line<T>& rhs) const {
            return !(*this == rhs)
        }

        bool contains (const Point<T>& point) const {
            check_validity();
            point.check_validity();

            if (p_ == point)
                return true;

            Vector point_vec {p_, point};
            return n_.orthogonal_to(point_vec);
        }
        
        bool parallel_to (const Line<T>& rhs) const {
            check_validity();
            rhs.check_validity();
            
            return n_.collinear_with(rhs.n_)
        }

        std::string to_string() const {
            return "Plane((" 
            + n_.to_string() + ", (x, y, z) -" 
            + p_.to_string() + ") = 0";
        }
    };
}