#pragma once

#include <concepts>
#include <string>
#include <vector>

// functions of built-in types is to be declared to be visible by concept 'HasLengthFun'
// (because of ADL: "argument-dependent lookup" (aka Koenig Lookup))
double Len(const std::string& s);
double Len(int n);

template<typename T>
concept HasLenFun = requires(T v)
{
    Len(v);
};

template<HasLenFun T>
double TotalLenFun(const std::vector<T>& vec)
{
    double len = 0.0;
    for (auto& v : vec)
        len += Len(v);
    return len;
}