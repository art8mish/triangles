#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>

#include <point.hpp>
#include <utils.hpp>

namespace triangles {
template <std::floating_point T> class Vector {
    T eps_{epsilon<T>()};

    T dx_ {0};
    T dy_ {0};
    T dz_ {0};

    bool validity_{false};
    void validate() {
        if (valid(dx_) && valid(dy_) && valid(dz_))
            validity_ = true;
    }

    void check_validity() const {
        if (!is_valid())
            throw std::logic_error(to_string() + " is not valid");
    }



public:
    Vector(const T &dx, const T &dy, const T &dz) : dx_{dx}, dy_{dy}, dz_{dz} {
        validate();
    }
    Vector(const T &dx, const T &dy) : Vector(dx, dy, 0) {}
    Vector(const T &dx) : Vector(dx, 0, 0) {}
    Vector() : Vector(0, 0, 0) {}

    Vector(const Point<T> &p) : Vector(p.x, p.y, p.z) {}

    Vector(const T &from_x, const T &from_y, const T &from_z,
           const T &to_x,   const T &to_y,   const T &to_z)
        : Vector(to_x - from_x, to_y - from_y, to_z - from_z) {}

    Vector(const Point<T> &from, const Point<T> &to)
        : Vector(from.x, from.y, from.z, to.x, to.y, to.z) {}

    bool is_valid() const {
        return validity_;
    }

    const T &x() const & {
        check_validity();
        return dx_;
    }
    const T &y() const & {
        check_validity();
        return dy_;
    }
    const T &z() const & {
        check_validity();
        return dz_;
    }

    bool operator==(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return equal<T>(dx_, rhs.dx_, eps_) &&
               equal<T>(dy_, rhs.dy_, eps_) &&
               equal<T>(dz_, rhs.dz_, eps_);
    }

    bool operator!=(const Vector<T> &rhs) const {
        return !(*this == rhs);
    }

    // Vector<T> operator +(const Vector<T> &rhs) const {
    //     check_validity();
    //     rhs.check_validity();

    //     return Vector<T>{dx_ + rhs.dx_, dy_ + rhs.dy_, dz_ + rhs.dz_}
    // }

    bool is_zero() const {
        check_validity();

        return zero<T>(dx_, eps_) && zero<T>(dy_, eps_) &&
               zero<T>(dz_, eps_);
    }

    // bool is_zero() const {
    //     check_validity();

    //     return zero<T>(dx_ * dx_ + dy_ * dy_ + dz_ * dz_, eps_ * eps_);
    // }

    bool is_normalized() const {
        check_validity();
        return equal<T>(dx_*dx_ + dy_*dy_ + dz_*dz_, 1, eps_);
    }

    T enorm() const {
        check_validity();
        return std::sqrt(edot(*this));
    }


    T edot(const Vector<T> &other) const {
        check_validity();
        other.check_validity();
        return dx_ * other.dx_ + dy_ * other.dy_ + dz_ * other.dz_;
    }

    // T edot(const Point<T> &point) const {
    //     check_validity();
    //     point.check_validity();
    //     return dx_ * point.x_ + dy_ * point.y_ + dz_ * point.z_;
    // }

    Vector<T> ecross(const Vector<T> &other) const {
        check_validity();
        other.check_validity();
        return Vector<T>{dy_ * other.dz_ - dz_ * other.dy_,
                         dz_ * other.dx_ - dx_ * other.dz_,
                         dx_ * other.dy_ - dy_ * other.dx_};
    }
    
    bool collinear_with(const Vector<T> &other) const {
        check_validity();
        other.check_validity();
        return ecross(other).is_zero();

        // T k_x = dx_ / other.dx_;
        // T k_y = dy_ / other.dy_;
        // T k_z = dz_ / other.dz_;
        // return equal<T>(k_x, k_y, eps_)
        //     && equal<T>(k_y, k_z, eps_);
    }

    bool orthogonal_to(const Vector<T> &other) const {
        check_validity();
        other.check_validity();

        return zero<T>(edot(other), eps_);
    }
    
    Vector<T>& normalize() & {
        check_validity();
        T norm = enorm();
        if (zero<T>(norm, eps_) || equal<T>(norm, 1, eps_))
            return *this;
            
        assert(zero<T>(norm, eps_) == false);
        dx_ = dx_ / norm;
        dy_ = dy_ / norm;
        dz_ = dz_ / norm;

        return *this;
    }

    Vector<T> normalize() && {
        check_validity();
        T norm = enorm();
        if (zero<T>(norm, eps_) || equal<T>(norm, 1, eps_))
            return Vector<T> {*this};
        
        assert(zero<T>(norm, eps_) == false);
        return Vector<T> {dx_ / norm, dy_ / norm, dz_ / norm};
    }


    Vector<T> get_perpendicular() {
        check_validity();
        if (is_zero())
            return Vector<T> {};

        if (std::abs(dx_) < std::abs(dy_) && std::abs(dx_) < std::abs(dz_))
            return ecross(Vector<T> {1, 0, 0});
        else if (std::abs(dy_) < std::abs(dz_))
            return ecross(Vector<T> {0, 1, 0});
        else
            return ecross(Vector<T> {0, 0, 1});
    }

    std::string to_string() const {
        return "Vec(" + std::to_string(dx_) + ", " +
               std::to_string(dy_) + ", " + std::to_string(dz_) + ")";
    }
};
} // namespace triangles