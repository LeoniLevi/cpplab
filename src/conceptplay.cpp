#include "conceptplay.h"



#include <numeric>
#include <concepts>
#include <vector>

#include <string>

template<typename T>
requires std::integral<T> || std::floating_point<T>
constexpr double Average(const std::vector<T>& vec)
{
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

template<typename T>
concept HasLength = requires(T v)
{
    {v.length()} -> std::convertible_to<double>;
};

// functions of built-in types is to be declared to be visible by concept 'HasLengthFun'
// (because of ADL: "argument-dependent lookup" (aka Koenig Lookup))
double Len(const std::string& s);
double Len(int n);

template<typename T>
concept HasLenFun = requires(T v)
{
    //{Len(v)} -> std::convertible_to<double>;
    Len(v);
};

template<HasLength T>
double TotalLength(const std::vector<T>& vec)
{
    double len = 0.0;
    for (auto & v : vec)
        len += v.length();
    return len;
}

template<HasLenFun T>
double TotalLenFun(const std::vector<T>& vec)
{
    double len = 0.0;
    for (auto& v : vec)
        len += Len(v);
    return len;
}

//-////////////////////////////
#include <math.h>
#include <string>

class Vector2D {
    double x;
    double y;
public:
    Vector2D(double x, double y) : x(x), y(y) {}
    double length() const { return sqrt(x * x + y * y); }
};
double Len(const Vector2D& v) { return v.length(); }
static_assert(HasLenFun<Vector2D>);


struct Point {
    int x;
    int y;
};
double Len(const Point& p) { return p.x + p.y; }
static_assert(HasLenFun<Point>);

// Next two funcs(with builtin params) are to be declared Before 'HasLengthFun' definition !!
double Len(int n) { return n; }
static_assert(HasLenFun<int>);

double Len(const std::string& s) { return (double)s.length(); }
static_assert(HasLenFun<std::string>);


void play_concepts()
{
    printf(" ==== play_concepts..\n");
    std::vector ints{ 1, 2, 3, 4, 5 };
    double avg1 = Average(ints);

    std::vector doubles{ 1.5, 2.5, 3.4, 4.4, 5.3, 6.3, 7.2 };
    double avg2 = Average(doubles);
    printf(" ~~ Average: ofInts=%f; ofDoubles=%f\n", avg1, avg2);

    std::vector<std::string> strings{ "aaa", "bbb", "ccc" };
    //double avgs = Average(strings); // ERROR!
    double slen = TotalLength(strings);

    //std::vector gvects{ Vector2D(1.1, 1.1), Vector2D{2.2, 2.2}, Vector2D{3.3, 3.3} };
    std::vector< Vector2D> gvects{ {1.1, 1.1}, { 2.2, 2.2 }, { 3.3, 3.3 } };
    double vlen = TotalLength(gvects);
    printf(" ~~ TotalLen: ofStrings=%f; ofVector2Ds=%f\n", slen, vlen);

    std::vector<Point> points{ {3, 4}, { 1, 2 }, { 5, 6 }};

    double nlens = TotalLenFun(ints); // ERROR!??
    printf(" ~~ TotalLenFun result: ofInts=%f\n", nlens);
    double vlens = TotalLenFun(strings); // ERROR!??
    printf(" ~~ TotalLenFun result: ofStrings=%f\n", vlens);
    double vlen2 = TotalLenFun(gvects);
    printf(" ~~ TotalLenFun result: ofVector2Ds=%f\n", vlen2);

    //double dlen = TotalLengthFun(doubles); // ERROR!
    //printf(" ~~ TotalLengthFun result: ofDoubles=%f\n", dlen);
    double ptlens = TotalLenFun(points); // ERROR!??
    printf(" ~~ TotalLengthFun result: ofPoints=%f\n", ptlens);

}