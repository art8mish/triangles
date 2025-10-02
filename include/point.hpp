
#include <string>
#include <concepts>
#include <cmath>
#include <limits>

#include <./utils.hpp>

namespace triangles
{
    template<std::floating_point T = double>
    class Point {
    public:
        T x_ = std::numeric_limits<T>::quiet_NaN();
        T y_ = std::numeric_limits<T>::quiet_NaN();
        T z_ = std::numeric_limits<T>::quiet_NaN();
        T eps_ = get_epsilon<T>();

        Point() = default;
        Point(const T &x, const T &y, const T &z) :
            x_{x}, y_{y}, z_{z} {}

    
        bool valid() const {
            return std::isnormal(x_) 
                && std::isnormal(y_) 
                && std::isnormal(z_);
        }

        bool operator == (const Point<T>& other) const {
            return std::abs(x_ - other.x_) < eps_ 
                && std::abs(y_ - other.y_) < eps_ 
                && std::abs(z_ - other.z_) < eps_;
        }
        
        void to_string() const {
            return "Point(" 
            + std::to_string(x_) + ", "
            + std::to_string(y_) + ", "
            + std::to_string(z_) + ")";
        }
    };


    template<std::floating_point T>
    class Vector {
    public:
        T dx_ = std::numeric_limits<T>::quiet_NaN();
        T dy_ = std::numeric_limits<T>::quiet_NaN();
        T dz_ = std::numeric_limits<T>::quiet_NaN();
        T eps_ = get_epsilon<T>();

        Vector() = default;
        Vector(const T &dx, const T &dy, const T &dz) :
            dx_{dx}, dy_{dy}, dz_{dz} {}

        Vector(const Point<T> &from, const Point<T> &to) :
            dx_ {to.x_ - from.x_}, 
            dy_ {to.y_ - from.y_}, 
            dz_ {to.z_ - from.z_} {}

        Vector(const T &from_x, const T &from_y, const T &from_z,
               const T &to_x,   const T &to_y,   const T &to_z) :
            dx_{to_x - from_x}, 
            dy_{to_y - from_y}, 
            dz_{to_z - from_z} {}

        
        // think about vec(0)
        bool valid() const {
            return std::isnormal(dx_) 
                && std::isnormal(dy_) 
                && std::isnormal(dz_);
        }

        bool operator == (const Vector<T>& other) const {
            return std::abs(dx_ - other.dx_) < eps_ 
                && std::abs(dy_ - other.dy_) < eps_ 
                && std::abs(dz_ - other.dz_) < eps_;
        }

        bool is_null() const {
            return std::abs(dx_ - 0.0L) < eps_
                && std::abs(dy_ - 0.0L) < eps_
                && std::abs(dz_ - 0.0L) < eps_;
        }
    
        void to_string() const {
            return "Vector(" 
            + std::to_string(dx_) + ", "
            + std::to_string(dy_) + ", "
            + std::to_string(dz_) + ")";
        }
    };
}