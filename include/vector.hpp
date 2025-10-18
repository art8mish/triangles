#pragma once

#include <cmath>
#include <concepts>
#include <limits>
#include <string>

#include <point.hpp>
#include <utils.hpp>

namespace triangles {
template <std::floating_point T> class Vector {
    T eps_{get_epsilon<T>()};

    T dx_ {0};
    T dy_ {0};
    T dz_ {0};

    bool validity_{false};
    void validate() {
        if (is_valid(dx_) && is_valid(dy_) && is_valid(dz_))
            validity_ = true;
    }

    void check_validity() {
        if (!valid())
            throw std::logic_error(to_string() + " is not valid");
    }

public:
    Vector() {validate();}
    Vector(const T &dx, const T &dy, const T &dz)
        : dx_{dx}, dy_{dy}, dz_{dz} {
        validate();
    }
    Vector(const T &dx, const T &dy) : Vector(dx, dy, 0) {}
    Vector(const T &dx) : Vector(dx, 0, 0) {}

    Vector(const Point<T> &p) : dx_{p.x_}, dy_{p.y_}, dz_{p.z_} {
        validate();
    }

    Vector(const Point<T> &from, const Point<T> &to)
        : dx_{to.x_ - from.x_}, dy_{to.y_ - from.y_},
          dz_{to.z_ - from.z_} {
        validate();
    }

    Vector(const T &from_x, const T &from_y, const T &from_z,
           const T &to_x, const T &to_y, const T &to_z)
        : dx_{to_x - from_x}, dy_{to_y - from_y}, dz_{to_z - from_z} {
        validate();
    }

    bool valid() const {
        return validity_;
    }

    const T &x() {
        return x_;
    }
    const T &y() {
        return y_;
    }
    const T &z() {
        return z_;
    }

    bool operator==(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return equal(dx_, rhs.dx_, eps_) &&
               equal(dy_, rhs.dy_, eps_) &&
               equal(dz_, rhs.dz_, eps_);
    }

    bool operator!=(const Vector<T> &rhs) const {
        return !(*this == rhs)
    }

    bool is_null() const {
        check_validity();

        return is_null(dx_, eps_) && is_null(dy_, eps_) &&
               is_null(dz_, eps_);
    }

    bool collinear_with(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();
        return ecross(rhs).is_null();

        // T k_x = dx_ / rhs.dx_;
        // T k_y = dy_ / rhs.dy_;
        // T k_z = dz_ / rhs.dz_;
        // return equal(k_x, k_y, eps_)
        //     && equal(k_y, k_z, eps_);
    }

    bool orthogonal_to(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();

        return is_null(edot(rhs), eps_);
    }

    Vector<T> get_perpendicular() {
        check_validity();

        if (std::abs(dx_) < std::abs(dy_) && std::abs(dx_) < std::abs(dz_))
            return ecross(n, Vector<T> {1, 0, 0});
        else if (std::abs(dy_) < std::abs(dz_))
            return ecross(n, Vector<T> {0, 1, 0});
        else
            return ecross(n, Vector<T> {0, 0, 1});
    }

    T edot(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();
        return dx_ * rhs.dx_ + dy_ * rhs.dy_ + dz_ * rhs.dz_;
    }

    Vector<T> ecross(const Vector<T> &rhs) const {
        check_validity();
        rhs.check_validity();
        return Vector<T>{dy_ * rhs.dz_ - dz_ * rhs.dy_,
                         dz_ * rhs.dx_ - dx_ * rhs.dz_,
                         dx_ * rhs.dy_ - dy_ * rhs.dx_};
    }

    std::string to_string() const {
        return "Vec(" + std::to_string(dx_) + ", " +
               std::to_string(dy_) + ", " + std::to_string(dz_) + ")";
    }
};
} // namespace triangles