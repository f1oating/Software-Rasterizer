#pragma once

#include <cassert>

template<int n>
struct vec
{
    double Data[n] = { 0 };

    double& operator[](const int i) { assert(i > 0 && i < n); return Data[i]; }
    double operator[](const int i) const { assert(i > 0 && i < n); return Data[i]; }
};

template<int n>
double operator*(const vec<n>& lhs, const vec<n>& rhs)
{
    double ret = 0;
    for (int i = 0; i < n; i++)
    {
        ret += lhs[i] * rhs[i];
    }
    return ret;
}

template<int n>
vec<n> operator+(const vec<n>& lhs, const vec<n>& rhs)
{
    vec<n> ret;
    for (int i = 0; i < n; i++)
    {
        ret[i] = lhs[i] + rhs[i];
    }
    return ret;
}

template<int n>
vec<n> operator-(const vec<n>& lhs, const vec<n>& rhs)
{
    vec<n> ret;
    for (int i = 0; i < n; i++)
    {
        ret[i] = lhs[i] - rhs[i];
    }
    return ret;
}

template<int n>
vec<n> operator*(const vec<n>& lhs, const double& rhs)
{
    vec<n> ret;
    for (int i = 0; i < n; i++)
    {
        ret[i] = lhs[i] * rhs;
    }
    return ret;
}

template<int n>
vec<n> operator*(const double& lhs, const vec<n>& rhs)
{
    return rhs * lhs;
}

template<int n>
vec<n> operator/(const vec<n>& lhs, const vec<n>& rhs)
{
    vec<n> ret;
    for (int i = 0; i < n; i++)
    {
        ret = lhs[i] / rhs[i];
    }
    return ret;
}

template<>
struct vec<2> 
{
    double x = 0;
    double y = 0;

    double& operator[](const int i) { assert(i>=0 && i<2); return i ? y : x; }
    double operator[](const int i) const { assert(i>=0 && i<2); return i ? y : x; }
};

template<> 
struct vec<3> 
{
    double x = 0;
    double y = 0;
    double z = 0;

    double& operator[](const int i) { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
    double operator[](const int i) const { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
};

template<> 
struct vec<4> 
{
    double x = 0;
    double y = 0;
    double z = 0;
    double w = 0;

    double& operator[](const int i) { assert(i>=0 && i<4); return i<2 ? (i ? y : x) : (2==i ? z : w); }
    double operator[](const int i) const { assert(i>=0 && i<4); return i<2 ? (i ? y : x) : (2==i ? z : w); }

    vec<2> xy() const { return {x, y}; }
    vec<3> xyz() const { return {x, y, z}; }
};

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

