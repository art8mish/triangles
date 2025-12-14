#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <stdexcept>
#include <string>

#include "point.hpp"
#include "utils.hpp"

namespace triangles {
template <std::floating_point T> class Vector final {
    T eps_{epsilon<T>()};

    T dx_{0};
    T dy_{0};
    T dz_{0};

    void validate() const {
        if (!valid(dx_) || !valid(dy_) || !valid(dz_))
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Vector(T dx, T dy, T dz) : dx_{dx}, dy_{dy}, dz_{dz} {
        validate();
    }
    Vector(T dx, T dy) : Vector(dx, dy, 0) {}
    explicit Vector(T dx) : Vector(dx, 0, 0) {}
    Vector() : Vector(0, 0, 0) {}

    Vector(const Point<T> &p) : Vector(p.x, p.y, p.z) {}

    Vector(T from_x, T from_y, T from_z, T to_x, T to_y, T to_z)
        : Vector(to_x - from_x, to_y - from_y, to_z - from_z) {}

    Vector(const Point<T> &from, const Point<T> &to)
        : Vector(from.x, from.y, from.z, to.x, to.y, to.z) {}

    const T &x() const & {
        return dx_;
    }
    const T &y() const & {

        return dy_;
    }
    const T &z() const & {

        return dz_;
    }

    bool operator==(const Vector<T> &rhs) const {
        return equal<T>(dx_, rhs.dx_, eps_) && equal<T>(dy_, rhs.dy_, eps_) &&
               equal<T>(dz_, rhs.dz_, eps_);
    }

    bool operator!=(const Vector<T> &rhs) const {
        return !(*this == rhs);
    }

    bool is_zero() const {
        return zero<T>(dx_, eps_) && zero<T>(dy_, eps_) && zero<T>(dz_, eps_);
    }

    bool is_normalized() const {
        return equal<T>(dx_ * dx_ + dy_ * dy_ + dz_ * dz_, 1, eps_);
    }

    T enorm() const {
        return std::sqrt(edot(*this));
    }

    T edot(const Vector<T> &other) const {
        return dx_ * other.dx_ + dy_ * other.dy_ + dz_ * other.dz_;
    }

    Vector<T> ecross(const Vector<T> &other) const {
        return Vector<T>{dy_ * other.dz_ - dz_ * other.dy_, dz_ * other.dx_ - dx_ * other.dz_,
                         dx_ * other.dy_ - dy_ * other.dx_};
    }

    bool collinear_with(const Vector<T> &other) const {
        return ecross(other).is_zero();
    }

    bool orthogonal_to(const Vector<T> &other) const {
        return zero<T>(edot(other), eps_);
    }

    Vector<T> &normalize() & {
        T norm = enorm();
        if (zero<T>(norm, eps_) || equal<T>(norm, 1, eps_))
            return *this;

        assert(zero<T>(norm, eps_) == false);
        dx_ = dx_ / norm;
        dy_ = dy_ / norm;
        dz_ = dz_ / norm;

        return *this;
    }

    Vector<T> normalize() const && {
        T norm = enorm();
        if (zero<T>(norm, eps_) || equal<T>(norm, 1, eps_))
            return Vector<T>{*this};

        assert(zero<T>(norm, eps_) == false);
        return Vector<T>{dx_ / norm, dy_ / norm, dz_ / norm};
    }

    Vector<T> get_perpendicular() const {
        if (is_zero())
            return Vector<T>{};

        if (std::abs(dx_) < std::abs(dy_) && std::abs(dx_) < std::abs(dz_))
            return ecross(Vector<T>{1, 0, 0});
        else if (std::abs(dy_) < std::abs(dz_))
            return ecross(Vector<T>{0, 1, 0});
        else
            return ecross(Vector<T>{0, 0, 1});
    }

    std::string to_string() const {
        return "Vec(" + std::to_string(dx_) + ", " + std::to_string(dy_) + ", " +
               std::to_string(dz_) + ")";
    }
};
} // namespace triangles