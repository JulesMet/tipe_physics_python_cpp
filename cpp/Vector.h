#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <type_traits>
#include <functional>


//
// operations definitions
//

template <class Lhs, class Rhs>
using multiplication_t = decltype(std::declval<Lhs>() * std::declval<Rhs>());

template <class Lhs, class Rhs>
using division_t = decltype(std::declval<Lhs>() / std::declval<Rhs>());

template <class Lhs, class Rhs>
using addition_t = decltype(std::declval<Lhs>() + std::declval<Rhs>());

template <class Lhs, class Rhs>
using substraction_t = decltype(std::declval<Lhs>() - std::declval<Rhs>());


//
// type trait definition
//

template <class Lhs, class Rhs>
constexpr bool can_multiply = is_detected<multiplication_t, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_divide = is_detected<division_t, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_add = is_detected<addition_t Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_substract = is_detected<substraction_t, Lhs, Rhs>::value;

//////////////////////////////////////////////////
//////////////////   Vector 2   //////////////////
//////////////////////////////////////////////////

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2(T _x, T _y)
        : x(_x), y(_y)
    {
    }

    Vec2(const Vec2& vec)
        : x(vec.x), y(vec.y)
    {
    }

    //////////////// Basic methods

    double Magnitude() const
    {
        if(!can_multiply<T, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        return sqrt(x*x + y*y);
    }


    Vec2 Normalised() const
    {
        double magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide<T, double>)
        {
            throw "Error, impossible division\n";
        }        

        return Vec2(x/magnitude, y/magnitude);
    }

    Vec2 Normalise() const
    {
        double magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide<T, double>)
        {
            throw "Error, impossible division\n";
        }

        x /= magnitude;
        y /= magnitude;
        
        return *this;
    }

    Vec2 ortho() const
    {
        return Vec2(-y, x);
    }

    /////////// add operators

    template <typename Ty>
    Vec2&& operator+(const Vec2<Ty>& other) const
    {
        if(!can_add<T, Ty>)
        {
            throw "Error, impossible addition\n";
        }

        return Vec2<addition_t<T, Ty>>(x + other.x, y + other.y)
    }

    template<typename Ty>
    friend Vec2<Ty>&& operator+(const Vec2<Ty>& v1, const Vec2<Ty>& v2);

    template<typename Lhs, typename Rhs>
    friend Vec2<addition_t<Lhs, Rhs>>&& operator+(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

    template <typename Ty>
    void operator+=(const Vec2<Ty>& other) {
        if(!can_add<T, Ty>)
        {
            throw "Error, impossible addition\n";
        }
        x += other.x;
        y += other.y;
    }



    /////////// substract operator

    template <typename Ty>
    Vec2&& operator-(const Vec2<Ty>& other) const
    {
        if(!can_substract<T, Ty>)
        {
            throw "Error, impossible substraction\n";
        }
        return Vec2<substraction_t<T, Ty>>(x - other.x, y - other.y);
    }

    template<typename Ty>
    friend Vec2<Ty>&& operator-(const Vec2<Ty>& v1, const Vec2<Ty>& v2);

    template<typename Ty>
    void operator-=(const Vec2& other) {
        if(!can_substract<T, Ty>)
        {
            throw "Error, impossible substraction\n";
        }

        x -= other.x;
        y -= other.y;
    }



    /////////// scalar multiplication

    Vec2&& operator*(double f)
    {
        if(!can_multiply<T, double>)
        {
            throw "Error, impossible multiplication\n";
        }

        return Vec2(f * x, f * y);
    }

    /////////// vector-vector multiplication

    template <typename Ty>
    Vec2&& operator*(const Vec<Ty>& other)
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }
        return Vec2(x * other.x, y * other.y);
    }

};



//////////////////////////////////////////////////
//////////////////   Vector 3   //////////////////
//////////////////////////////////////////////////

template<typename T>
struct Vec3 {

    union
    {
        struct
        {
            T x, y, z;
        };

        struct
        {
            T r, g, b;
        };
    };

    Vec3(T _x, T _y, T _z)
        : x(_x), y(_y), z(_z)
    {
    }

    Vec3(const Vec3& vec)
        : x(vec.x), y(vec.y), z(vec.vec3)
    {
    }

    //////////////// Basic methods

    double Magnitude() const
    {
        return sqrt(x*x + y*y + z*z);
    }


    Vec3 Normalised() const
    {
        double magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        return Vec3(x/magnitude, y/magnitude, z/magnitude);
    }

    Vec3 Normalised() const
    {
        double magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        
        return *this;
    }


    /////////// add operators

    Vec3&& operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }

    template<typename Ty>
    friend Vec3<Ty>&& operator+(const Vec3<Ty>& v1, const Vec3<Ty>& v2);

    void operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }



    /////////// substract operator

    Vec3&& operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y); }

    template<typename Ty>
    friend Vec3<Ty>&& operator-(const Vec3<Ty>& v1, const Vec3<Ty>& v2);

    void operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    /////////// scalar multiplication

    Vec3&& operator*(double f)
    {
        return Vec3(f * x, f * y, f * z);
    }

    /////////// vector-vector multiplication


};








/////// Vector 2


template<typename Ty>
Vec2<Ty>&& operator+(const Vec2<Ty>& v1, const Vec2<Ty>& v2)
{
    return Vec2<Ty>(v1.x + v2.x, v1.y + v2.y);
}

template<typename Ty>
Vec2<Ty>&& operator-(const Vec2<Ty>& v1, const Vec2<Ty>& v2)
{
    return Vec2<Ty>(v1.x - v2.x, v1.y - v2.y);
}


// print operator Vec2
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec2<Ty>& obj) {
    os << "(" << obj.x << ", " << obj.y << ")";
    return os;
}





//////// Vector 3


template<typename Ty>
Vec3<Ty>&& operator+(const Vec3<Ty>& v1, const Vec3<Ty>& v2)
{
    return Vec3<Ty>(v1.x + v2.x, v1.y + v2.y);
}

template<typename Ty>
Vec3<Ty>&& operator-(const Vec3<Ty>& v1, const Vec3<Ty>& v2)
{
    return Vec3<Ty>(v1.x - v2.x, v1.y - v2.y);
}


// print operator Vec3
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec3<Ty>& obj) {
    os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
    return os;
}