#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <type_traits>
#include <functional>


using ldouble = long double;





////// stuff that I don't get currently but apparently I need it to make my type detector works


namespace detail 
{
    template <class Default, class AlwaysVoid,
            template<class...> class Op, class... Args>
    struct detector 
    {
        using value_t = std::false_type;
        using type = Default;
    };

    template <class Default, template<class...> class Op, class... Args>
    struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> 
    {
        using value_t = std::true_type;
        using type = Op<Args...>;
    }; 
}
    
struct nonesuch { };
 
template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;
 
template <template<class...> class Op, class... Args>
using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;
 
template <class Default, template<class...> class Op, class... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;








//
// operations definitions
//

template <class Lhs, class Rhs>
using multiplication_type = decltype(std::declval<Lhs>() * std::declval<Rhs>());

template <class Lhs, class Rhs>
using multiplication_equal_type = decltype(std::declval<Lhs>() *= std::declval<Rhs>());


template <class Lhs, class Rhs>
using division_type = decltype(std::declval<Lhs>() / std::declval<Rhs>());

template <class Lhs, class Rhs>
using division_equal_type = decltype(std::declval<Lhs>() /= std::declval<Rhs>());


template <class Lhs, class Rhs>
using addition_type = decltype(std::declval<Lhs>() + std::declval<Rhs>());

template <class Lhs, class Rhs>
using addition_equal_type = decltype(std::declval<Lhs>() += std::declval<Rhs>());


template <class Lhs, class Rhs>
using substraction_type = decltype(std::declval<Lhs>() - std::declval<Rhs>());

template <class Lhs, class Rhs>
using substraction_equal_type = decltype(std::declval<Lhs>() -= std::declval<Rhs>());


//
// type trait definition
//

template <class Lhs, class Rhs>
constexpr bool can_multiply = is_detected<multiplication_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_multiply_equal = is_detected<multiplication_equal_type, Lhs, Rhs>::value;


template <class Lhs, class Rhs>
constexpr bool can_divide = is_detected<division_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_divide_equal = is_detected<division_equal_type, Lhs, Rhs>::value;


template <class Lhs, class Rhs>
constexpr bool can_add = is_detected<addition_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_add_equal = is_detected<addition_equal_type, Lhs, Rhs>::value;


template <class Lhs, class Rhs>
constexpr bool can_substract = is_detected<substraction_type, Lhs, Rhs>::value;

template <class Lhs, class Rhs>
constexpr bool can_substract_equal = is_detected<substraction_equal_type, Lhs, Rhs>::value;


//////////// classes declaration
template<typename t>
class Vec2;

template<typename t>
class Vec3;



//////////////////////////////////////////////////////////////
//////////////////   Functions' signature   //////////////////
//////////////////////////////////////////////////////////////



/////// Vector 2

// additions

template<typename Lhs, typename Rhs>
Vec2<addition_type<Lhs, Rhs>> operator+(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);


// substraction

template<typename Lhs, typename Rhs>
Vec2<substraction_type<Lhs, Rhs>> operator-(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);



// multiplications

template <typename T>
Vec2<division_type<ldouble, T>> operator*(ldouble f, const Vec2<T>& v);

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>> operator*(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);



// divisions

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>> operator/(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);


// print operator Vec2
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec2<Ty>& obj);


/////// dot product

template<typename Lhs, typename Rhs>
ldouble dot(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);



/////// distance between 2 vector

template<typename Lhs, typename Rhs>
ldouble dist(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);

template<typename Lhs, typename Rhs>
ldouble dist_square(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2);







//////// Vector 3

// additions

template<typename Lhs, typename Rhs>
Vec3<addition_type<Lhs, Rhs>> operator+(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);


// substraction

template<typename Lhs, typename Rhs>
Vec3<substraction_type<Lhs, Rhs>> operator-(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);



// multiplications

template <typename T>
Vec3<division_type<ldouble, T>> operator*(ldouble f, const Vec3<T>& v);

template<typename Lhs, typename Rhs>
Vec3<division_type<Lhs, Rhs>> operator*(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);



// divisions

template<typename Lhs, typename Rhs>
Vec3<division_type<Lhs, Rhs>> operator/(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);


// print operator Vec3
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec3<Ty>& obj);


/////// dot product

template<typename Lhs, typename Rhs>
ldouble dot(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);


/////// distance between 2 vector

template<typename Lhs, typename Rhs>
ldouble dist(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);

template<typename Lhs, typename Rhs>
ldouble dist_square(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2);









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

    ldouble Magnitude() const
    {
        if(!can_multiply<T, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(!can_add<multiplication_type<T, T>, multiplication_type<T, T>>)
        {
            throw "Error, impossible addition\n";
        }

        return sqrt(x*x + y*y);
    }

    ldouble Magnitude_squared() const
    {
        if(!can_multiply<T, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(!can_add<multiplication_type<T, T>, multiplication_type<T, T>>)
        {
            throw "Error, impossible addition\n";
        }

        return x*x + y*y;
    }


    Vec2 Normalised() const
    {
        ldouble magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide<T, ldouble>)
        {
            throw "Error, impossible division\n";
        }        

        return Vec2(x/magnitude, y/magnitude);
    }

    Vec2 Normalise()
    {
        ldouble magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide_equal<T, ldouble>)
            throw "Error, impossible division\n";

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
    Vec2<addition_type<T, Ty>> operator+(const Vec2<Ty>& other) const
    {
        if(!can_add<T, Ty>)
        {
            throw "Error, impossible addition\n";
        }

        return Vec2<addition_type<T, Ty>>(x + other.x, y + other.y);
    }

    void operator+=(const Vec2& other) {
        if(!can_add<T, T>)
        {
            std::cout << "test\n";
            throw "Error, impossible addition\n";
        }
        x += other.x;
        y += other.y;
    }



    /////////// substract operator

    template <typename Ty>
    Vec2<substraction_type<T, Ty>> operator-(const Vec2<Ty>& other) const
    {
        if(!can_substract<T, Ty>)
        {
            throw "Error, impossible substraction\n";
        }
        return Vec2<substraction_type<T, Ty>>(x - other.x, y - other.y);
    }

    void operator-=(const Vec2& other) {
        if(!can_substract_equal<T, T>)
        {
            throw "Error, impossible substraction\n";
        }

        x -= other.x;
        y -= other.y;
    }



    /////////// scalar multiplication

    Vec2<multiplication_type<T, ldouble>> operator*(ldouble f) const
    {
        if(!can_multiply<ldouble, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        return Vec2<multiplication_type<T, ldouble>>(x * f, y * f);
    }

    void operator*=(ldouble f)
    {
        if(!can_multiply_equal<T, ldouble>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= f;
        y *= f;
    }

    /////////// vector-vector multiplication (component-wise)

    template <typename Ty>
    Vec2<multiplication_type<T, Ty>> operator*(const Vec2<Ty>& other) const
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }
        return Vec2<multiplication_type<T, Ty>>(x * other.x, y * other.y);
    }

    template<typename Ty>
    void operator*=(const Vec2<Ty>& v)
    {
        if(!can_multiply_equal<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= v.x;
        y *= v.y;
    }



    /////////// scalar division

    Vec2<division_type<T, ldouble>> operator/(ldouble f) const
    {
        if(!can_divide<T, ldouble>)
        {
            throw "Error, impossible division\n";
        }

        if(f == 0)
        {
            throw "Division by zero\n";
        }

        return Vec2<division_type<T, ldouble>>(x / f, y / f);
    }

    void operator/=(ldouble f)
    {
        if(!can_divide_equal<T, ldouble>)
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
    Vec2<division_type<T, Ty>> operator/(const Vec2<Ty>& other) const
    {
        if(!can_divide<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(other.x == 0 || other.y == 0)
        {
            throw "Division by zero\n";
        }

        return Vec2<division_type<T, Ty>>(x / other.x, y / other.y);
    }

    template<typename Ty>
    void operator/=(const Vec2<Ty>& v)
    {
        if(!can_divide_equal<T, Ty>)
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

    ldouble Magnitude() const
    {
        if(!can_multiply<T, T>)
            throw "Error, impossible multiplication\n";
        if(!can_add<multiplication_type<T, T>, multiplication_type<T, T>>)
            throw "Error, impossible addition\n";

        return sqrt(x*x + y*y + z*z);
    }

    ldouble Magnitude_squared() const
    {
        if(!can_multiply<T, T>)
            throw "Error, impossible multiplication\n";
        if(!can_add<multiplication_type<T, T>, multiplication_type<T, T>>)
            throw "Error, impossible addition\n";

        return x*x + y*y + z*z;
    }


    Vec3 Normalised() const
    {
        ldouble magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide<T, ldouble>)
            throw "Error, impossible division\n";

        return Vec3(x/magnitude, y/magnitude, z/magnitude);
    }

    Vec3 Normalise() const
    {
        ldouble magnitude = Magnitude();
        if(magnitude == 0)
        {
            return *this;
        }

        if(!can_divide_equal<T, ldouble>)
            throw "Error, impossible division\n";

        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        
        return *this;
    }


    /////////// add operators

    template <typename Ty>
    Vec3<addition_type<T, Ty>> operator+(const Vec3<Ty>& other) const
    {
        if(!can_add<T, Ty>)
        {
            throw "Error, impossible addition\n";
        }

        return Vec3<addition_type<T, Ty>>(x + other.x, y + other.y, z + other.z);
    }

    void operator+=(const Vec3& other) {
        if(!can_add_equal<T, T>)
        {
            throw "Error, impossible addition\n";
        }
        x += other.x;
        y += other.y;
        z += other.z;
    }



    /////////// substract operator

    template <typename Ty>
    Vec3<substraction_type<T, Ty>> operator-(const Vec3<Ty>& other) const
    {
        if(!can_substract<T, Ty>)
        {
            throw "Error, impossible substraction\n";
        }
        return Vec3<substraction_type<T, Ty>>(x - other.x, y - other.y, z - other.z);
    }

    void operator-=(const Vec3& other) {
        if(!can_substract_equal<T, T>)
        {
            throw "Error, impossible substraction\n";
        }

        x -= other.x;
        y -= other.y;
        z -= other.z;
    }



    /////////// scalar multiplication

    Vec3<multiplication_type<T, ldouble>> operator*(ldouble f) const
    {
        if(!can_multiply<ldouble, T>)
        {
            throw "Error, impossible multiplication\n";
        }

        return Vec3<multiplication_type<T, ldouble>>(x * f, y * f, z * f);
    }

    void operator*=(ldouble f)
    {
        if(!can_multiply_equal<T, ldouble>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= f;
        y *= f;
        z *= f;
    }

    /////////// vector-vector multiplication (component-wise)

    template <typename Ty>
    Vec3<multiplication_type<T, Ty>> operator*(const Vec3<Ty>& other) const
    {
        if(!can_multiply<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }
        return Vec3<multiplication_type<T, Ty>>(x * other.x, y * other.y, z * other.z);
    }

    template<typename Ty>
    void operator*=(const Vec3<Ty>& v)
    {
        if(!can_multiply_equal<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        x *= v.x;
        y *= v.y;
        z *= v.z;
    }



    /////////// scalar division

    Vec3<division_type<T, ldouble>> operator/(ldouble f) const
    {
        if(!can_divide<T, ldouble>)
        {
            throw "Error, impossible division\n";
        }

        if(f == 0)
        {
            throw "Division by zero\n";
        }

        return Vec3<division_type<T, ldouble>>(x / f, y / f, z / f);
    }

    void operator/=(ldouble f)
    {
        if(!can_divide<T, ldouble>)
        {
            throw "Error, impossible division\n";
        }

        if(f == 0)
        {
            throw "Division by zero\n";
        }

        x /= f;
        y /= f;
        z /= f;
    }

    /////////// vector-vector division (component-wise)

    template <typename Ty>
    Vec3<division_type<T, Ty>> operator*(const Vec3<Ty>& other) const
    {
        if(!can_divide<T, Ty>)
        {
            throw "Error, impossible multiplication\n";
        }

        if(other.x == 0 || other.y == 0)
        {
            throw "Division by zero\n";
        }

        return Vec3<division_type<T, Ty>>(x / other.x, y / other.y, z / other.z);
    }

    template<typename Ty>
    void operator/=(const Vec3<Ty>& v)
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
        z /= v.z;
    }
};











/////// Vector 2

// additions

template<typename Lhs, typename Rhs>
Vec2<addition_type<Lhs, Rhs>> operator+(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_add<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec2<addition_type<Lhs, Rhs>>(v1.x + v2.x, v1.y + v2.y);
}




// substraction

template<typename Lhs, typename Rhs>
Vec2<substraction_type<Lhs, Rhs>> operator-(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_substract<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec2<substraction_type<Lhs, Rhs>>(v1.x - v2.x, v1.y - v2.y);
}



// multiplications

template <typename T>
Vec2<division_type<ldouble, T>> operator*(ldouble f, const Vec2<T>& v)
{
    if(!can_multiply<ldouble, T>)
    {
        throw "Error, impossible multiplication\n";
    }

    return Vec2<division_type<ldouble, T>>(f * v.x, f * v.y);
}

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>> operator*(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_multiply<Lhs, Rhs>)
    {
        throw "Error, impossible multiplication\n";
    }

    return Vec2<division_type<Lhs, Rhs>>(v1.x * v2.x, v1.y * v2.y);
}



// divisions

template<typename Lhs, typename Rhs>
Vec2<division_type<Lhs, Rhs>> operator/(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
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

/////// dot product

template<typename Lhs, typename Rhs>
ldouble dot(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    if(!can_multiply<Lhs, Rhs>)
        throw "Error, impossible multiplication\n";
    if(!can_add<multiplication_type<Lhs, Rhs>, multiplication_type<Lhs, Rhs>>)
        throw "Error, Impossible addition\n";

    return v1.x * v2.x + v1.y * v2.y;
}


/////// distance between 2 vector

template<typename Lhs, typename Rhs>
ldouble dist(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    const Vec2<substraction_type<Lhs, Rhs>> deplacement_vector =  v2 - v1;

    return deplacement_vector.Magnitude();
}

template<typename Lhs, typename Rhs>
ldouble dist_square(const Vec2<Lhs>& v1, const Vec2<Rhs>& v2)
{
    const Vec2<substraction_type<Lhs, Rhs>> deplacement_vector =  v2 - v1;

    return dot(deplacement_vector, deplacement_vector);
}









//////// Vector 3

// additions

template<typename Lhs, typename Rhs>
Vec3<addition_type<Lhs, Rhs>> operator+(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    if(!can_add<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec3<addition_type<Lhs, Rhs>>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}




// substraction

template<typename Lhs, typename Rhs>
Vec3<substraction_type<Lhs, Rhs>> operator-(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    if(!can_substract<Lhs, Rhs>)
    {
        throw "Error, impossible addition\n";
    }

    return Vec3<substraction_type<Lhs, Rhs>>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}



// multiplications

template <typename T>
Vec3<division_type<ldouble, T>> operator*(ldouble f, const Vec3<T>& v)
{
    if(!can_multiply<ldouble, T>)
    {
        throw "Error, impossible multiplication\n";
    }

    return Vec3<division_type<ldouble, T>>(f * v.x, f * v.y, f * v.z);
}

template<typename Lhs, typename Rhs>
Vec3<division_type<Lhs, Rhs>> operator*(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    if(!can_multiply<Lhs, Rhs>)
    {
        throw "Error, impossible multiplication\n";
    }

    return Vec3<division_type<Lhs, Rhs>>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}



// divisions

template<typename Lhs, typename Rhs>
Vec3<division_type<Lhs, Rhs>> operator/(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    if(!can_divide<Lhs, Rhs>)
    {
        throw "Error, impossible division\n";
    }

    if (v2.x == 0 || v2.y == 0 || v2.z == 0)
    {
        throw "Division by zero\n";
    }

    return Vec3<division_type<Lhs, Rhs>>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}


// print operator Vec3
template<typename Ty>
std::ostream& operator<<(std::ostream& os, const Vec3<Ty>& obj) {
    os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
    return os;
}


/////// dot product

template<typename Lhs, typename Rhs>
ldouble dot(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    if(!can_multiply<Lhs, Rhs>)
        throw "Error, impossible multiplication\n";
    if(!can_add<multiplication_type<Lhs, Rhs>, multiplication_type<Lhs, Rhs>>)
        throw "Error, Impossible addition\n";

    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


/////// distance between 2 vector

template<typename Lhs, typename Rhs>
ldouble dist(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    const Vec3<substraction_type<Lhs, Rhs>> deplacement_vector =  v2 - v1;

    return deplacement_vector.Magnitude();
}

template<typename Lhs, typename Rhs>
ldouble dist_square(const Vec3<Lhs>& v1, const Vec3<Rhs>& v2)
{
    const Vec3<substraction_type<Lhs, Rhs>> deplacement_vector = v2 - v1;

    return dot(deplacement_vector, deplacement_vector);
}