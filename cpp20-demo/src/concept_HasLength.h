#pragma once

#include <concepts>
#include <vector>

template<typename T>
concept HasLength = requires(T v)
{
    {v.length()} -> std::convertible_to<double>;
};

template<HasLength T>
double TotalLength(const std::vector<T>& vec)
{
    double len = 0.0;
    for (auto & v : vec)
        len += v.length();
    return len;
}
