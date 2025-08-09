#pragma once

#include <concepts>
#include <string>

// == Trick which allows define HasLen2Fun before declaration of Len2 for builtin types...
// == But, we still need to declare Len2 before function using HasLen2Fun types ...

template<class T>
struct A {
    operator T() const;
};

template<typename T>
concept HasLen2Fun = requires
{
    Len2(A<T>{});
};

double Len2(short b);
static_assert(HasLen2Fun<short>);

double Len2(std::string b);
static_assert(HasLen2Fun<std::string>);


template<HasLen2Fun T>
double TotalLen2Fun(const std::vector<T>& vec)
{
    double len = 0.0;
    for (auto& v : vec)
        len += Len2(v);
    return len;
}


double Len2(short b) { return b; }
double Len2(std::string s) { return (double)s.length(); }
