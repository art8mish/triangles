#pragma once

#include <string>
#include <concepts>
#include <cmath>
#include <limits>

#include <./utils.hpp>


namespace triangles
{
    template<std::floating_point T = double>
    class Vector {
        T eps_ {get_epsilon<T>()};

        T dx_ {std::numeric_limits<T>::quiet_NaN()};
        T dy_ {std::numeric_limits<T>::quiet_NaN()};
        T dz_ {std::numeric_limits<T>::quiet_NaN()};

        bool validity_ {false};
        void validate() {
            if (is_valid(dx_) && is_valid(dy_) && is_valid(dz_))
                validity_ = true;
        }

        void check_validity() {
            if (!valid())
                throw std::logic_error(to_string()+" is not valid");
        }

    public:
        Vector() = default;
        Vector(const T &dx, const T &dy, const T &dz) :
            dx_{dx}, dy_{dy}, dz_{dz} {validate();}

        Vector(const Point<T> &from, const Point<T> &to) :
            dx_ {to.x_ - from.x_}, 
            dy_ {to.y_ - from.y_}, 
            dz_ {to.z_ - from.z_} {validate();}

        Vector(const T &from_x, const T &from_y, const T &from_z,
               const T &to_x,   const T &to_y,   const T &to_z) :
            dx_{to_x - from_x}, 
            dy_{to_y - from_y}, 
            dz_{to_z - from_z} {validate();}

        bool valid() const {
            return validity_;
        }

        bool operator== (const Vector<T>& rhs) const {
            check_validity();
            rhs.check_validity();
            
            return is_equal(dx_, rhs.dx_, eps_)
                && is_equal(dy_, rhs.dy_, eps_)
                && is_equal(dz_, rhs.dz_, eps_);
        }

        bool operator != (const Vector<T>& rhs) const {
            return !(*this == rhs)
        }

        bool is_null() const {
            check_validity();

            return is_null(dx_, eps_)
                && is_null(dy_, eps_)
                && is_null(dz_, eps_);
        }

        bool collinear_with (const Vector<T>& rhs) const {
            check_validity();
            rhs.check_validity();

            T k_x = dx_ / rhs.dx_;
            T k_y = dy_ / rhs.dy_;
            T k_z = dz_ / rhs.dz_;
            return is_equal(k_x, k_y, eps_)
                && is_equal(k_y, k_z, eps_);
        }

        bool orthogonal_to (const Vector<T>& rhs) const {
            check_validity();
            rhs.check_validity();

            return is_null(edot(rhs),  eps_);
        }

        T edot (const Vector<T>& rhs) const {
            check_validity();
            rhs.check_validity();
            return dx_ * rhs.dx_
                 + dy_ * rhs.dy_
                 + dz_ * rhs.dz_;
        }

        Vector ecross(const Vector<T>& rhs) const {
            check_validity();
            rhs.check_validity();
            return Vector{
                dy_ * rhs.dz_ - dz_ * rhs.dy_,
                dz_ * rhs.dx_ - dx_ * rhs.dz_,
                dx_ * rhs.dy_ - dy_ * rhs.dx_
            };
        }

        std::string to_string() const {
            return "Vec(" 
            + std::to_string(dx_) + ", "
            + std::to_string(dy_) + ", "
            + std::to_string(dz_) + ")";
        }
    };
}