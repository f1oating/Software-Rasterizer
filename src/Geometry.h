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