
#include <string>
#include <concepts>
#include <cmath>

#include <./utils.hpp>

namespace triangles {
    template<std::floating_point T>
    class Line {
        // L: p_ + vec(d_) * t
        Point p_ {};
        Vector d_ {};

    public:
        Line() = default;
        Line(const Point<T> &p1, const Point<T> &p2) :
            p_ {p1}, d_ {p1, p2} {}

        Line(const T &x1, const T &y1, const T &z1,
             const T &x2, const T &y2, const T &z2) :
            p_ {x1, y1, z1}, d_ {x1, y1, z1, x2, y2, z2} {}

        bool valid() const {


            return std::isnormal(x_) 
                && std::isnormal(y_) 
                && std::isnormal(z_);
        }

        bool operator == (const Line<T>& other) const {
            return p_ == other.p_ 
                && d_ == other.d_;
        }

        void to_string() const {
            return "Line(" 
            + p_.to_string() + " + "
            + d_.to_string() + "* t)";
        }
    };
}