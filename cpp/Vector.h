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
using multiplication_type = decltype(std::declval<Lhs>() * std::declval<Rhs>());

template <class Lhs, class Rhs>
using division_type = decltype(std::declval<Lhs>() / std::declval<Rhs>());

template <class Lhs, class Rhs>
using addition_type = decltype(std::declval<Lhs>() + std::declval<Rhs>());

template <class Lhs, class Rhs>
using substraction_type = decltype(std::declval<Lhs>() - std::declval<Rhs>());


//
// type trait definition
//

template <class Lhs, class Rhs>
constexpr bool can_multiply = is_detected<multiplication_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_divide = is_detected<division_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_add = is_detected<addition_type Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_substract = is_detected<substraction_type, Lhs, Rhs>::value;

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
    Vec2<addition_type<T, Ty>>&& operator+(const Vec2<Ty>& other) const
    {
        if(!can_add<T, Ty>)
        {
            throw "Error, impossible addition\n";
        }

        return Vec2<addition_type<T, Ty>>(x + other.x, y + other.y)
    }

    friend Vec2&& operator+(const Vec2& v1, const Vec2& v2);

    template<typename Lhs, typename Rhs>
    friend Vec2<addition_type<Lhs, Rhs>>&& operator+(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

    void operator+=(const Vec2& other) {
        if(!can_add<T, T>)
        {
            throw "Error, impossible addition\n";
        }
        x += other.x;
        y += other.y;
    }



    /////////// substract operator

    template <typename Ty>
    Vec2<substraction_type<T, Ty>>&& operator-(const Vec2<Ty>& other) const
    {
        if(!can_substract<T, Ty>)
        {
            throw "Error, impossible substraction\n";
        }
        return Vec2<substraction_type<T, Ty>>(x - other.x, y - other.y);
    }

    friend Vec2&& operator-(const Vec2& v1, const Vec2& v2);

    template<typename Lhs, typename Rhs>
    friend Vec2<substraction_type<Lhs, Rhs>>&& operator-(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

    void operator-=(const Vec2& other) {
        if(!can_substract<T, T>)
        {
            throw "Error, impossible substraction\n";
        }

        x -= other.x;
        y -= other.y;
    }



    /////////// scalar multiplication

    Vec2&& operator*(double f)
    {
        if(!can_multiply<double, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        return Vec2(f * x, f * y);
    }

    friend Vec2&& operator*(double f, const Vec2& v);

    void operator*=(double f)
    {
        if(!can_multiply<T, double>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= f;
        y *= f;
    }

    /////////// vector-vector multiplication (component-wise)

    template <typename Ty>
    Vec2<multiplication_type<T, Ty>>&& operator*(const Vec<Ty>& other)
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }
        return Vec2(x * other.x, y * other.y);
    }

    friend Vec2&& operator*(const Vec2& v1, const Vec2& v2);

    template<typename Lhs, typename Rhs>
    friend Vec2<multiplication_type<Lhs, Rhs>>&& operator*(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

    template<typename Ty>
    void operator*=(const Vec2<Ty>& v)
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= v.x;
        y *= v.y;
    }



    /////////// scalar division

    Vec2&& operator/(double f)
    {
        if(!can_divide<T, double>)
        {
            throw "Error, impossible division\n";
        }

        if(f == 0)
        {
            throw "Division by zero\n";
        }

        return Vec2(x / f, y / f);
    }

    void operator/=(double f)
    {
        if(!can_divide<T, double>)
        {
            throw "Error, impossible division\n";
        }

        if(f == 0)
        {
            throw "Division by zero\n";
        }

        x /= f;
        y /= f;
    }

    /////////// vector-vector division (component-wise)

    template <typename Ty>
    Vec2<division_type<T, Ty>>&& operator*(const Vec<Ty>& other)
    {
        if(!can_divide<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(other.x == 0 || other.y == 0)
        {
            throw "Division by zero\n";
        }

        return Vec2(x / other.x, y / other.y);
    }

    friend Vec2&& operator/(const Vec2& v1, const Vec2& v2);

    template<typename Lhs, typename Rhs>
    friend Vec2<division_type<Lhs, Rhs>>&& operator/(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

    template<typename Ty>
    void operator/=(const Vec2<Ty>& v)
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(v.x == 0 || v.y == 0)
        {
            throw "Division by zero\n";
        }

        x /= v.x;
        y /= v.y;
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

// additions

template<typename T>
Vec2<T>&& operator+(const Vec2<T>& v1, const Vec2<T>& v2)
{
    if(!can_add<T, T>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec2<T>(v1.x + v2.x, v1.y + v2.y);
}

template<typename Lhs, typename Rhs>
Vec2<addition_type<Lhs, Rhs>>&& operator+(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_add<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec2<addition_type<Lhs, Rhs>>(v1.x + v2.x, v1.y + v2.y);
}




// substractions

template<typename T>
Vec2<T>&& operator-(const Vec2<T>& v1, const Vec2<T>& v2)
{
    if(!can_substract<T, T>)
    {
        throw "Error, impossible substraction\n";
    }
    return Vec2<T>(v1.x - v2.x, v1.y - v2.y);
}

template<typename Lhs, typename Rhs>
Vec2<substraction_type<Lhs, Rhs>>&& operator-(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_substract<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec2<substraction_type<Lhs, Rhs>>(v1.x - v2.x, v1.y - v2.y);
}



// multiplications

template <typename T>
Vec2<T>&& operator*(double f, const Vec2<T>& v)
{
    return v*f;
}

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>>&& operator*(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_multiply<Lhs, Rhs>)
    {
        throw "Error, impossible multiplication\n";
    }

    return Vec2<division_type<Lhs, Rhs>>(v1.x * v2.x, v1.y * v2.y);
}



// divisions

template<typename T>
Vec2<T>&& operator/(const Vec2<T>& v1, const Vec2<T>& v2)
{
    if(!can_divide<T, T>)
    {
        throw "Error, impossible division\n";
    }

    if (v2.x == 0 || v2.y == 0)
    {
        throw "Division by zero\n";
    }

    return Vec2<T>(v1.x / v2.x, v1.y / v2.y);
}

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>>&& operator/(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_divide<Lhs, Rhs>)
    {
        throw "Error, impossible division\n";
    }

    if (v2.x == 0 || v2.y == 0)
    {
        throw "Division by zero\n";
    }

    return Vec2<division_type<Lhs, Rhs>>(v1.x / v2.x, v1.y / v2.y);
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