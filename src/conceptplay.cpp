#include "conceptplay.h"

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

template<HasLength T>
double TotalLength( std::vector<T>& vec)
{
    double len = 0.0;
    for (auto & v : vec)
        len += v.length();
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
    double length() { return sqrt(x * x + y * y); }
};

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

    std::vector gvects{ Vector2D(1.1, 1.1), Vector2D{2.2, 2.2}, Vector2D{3.3, 3.3} };
    double vlen = TotalLength(gvects);
    printf(" ~~ TotalLen: ofStrings=%f; ofVector2Ds=%f\n", slen, vlen);

    //double dlen = TotalLength(doubles); // ERROR!

}