#pragma once

#include <concepts>
#include <optional>
#include <vector>
#include <ranges>
#include <functional>

// Concept for a Monadic type
template <typename M, typename T>
concept Monadic = requires(M m, T val, std::function<std::optional<int>(T)> f) {
    // pure/return operation
    { M::template pure<T>(val) } -> std::same_as<M>;
    // bind operation (operator |)
    { m | f } -> std::same_as<M>;
};

// Monadic operations for std::optional
namespace optional_monad {
    template <typename T>
    std::optional<T> pure(T val) {
        return std::make_optional(val);
    }

    template <typename T, typename Func, typename U = std::invoke_result_t<Func, T>::value_type>
    std::optional<U> operator | (std::optional<T> opt, Func f) {
        if (opt) {
            return f(*opt);
        } else {
            return std::nullopt;
        }
    }
} // namespace optional_monad

namespace vector_monad {
    template <typename T>
    std::vector<T> pure(T val) { return std::vector<T>(1, val);}

    template <typename T, typename Func, typename U = std::invoke_result_t<Func, T>::value_type>
    std::vector<U> operator | (std::vector<T> vect, Func f) {
        std::vector<U> result;
        for (const T& elem: vect) {
            std::vector<U> vval = f(elem);
            //result.push_back(f(elem));
            for (auto const& val: vval)
                result.push_back(val);
        }
        return result;
    }
}

//=============================

#include <concepts>
#include <type_traits>
#include <utility>

// Concept for a type that can be "unit-constructed"
template <typename M, typename T>
concept HasUnit = requires(T val) {
    { M::unit(val) } -> std::same_as<M>; // Assumes static unit method
    // Or, for a constructor:
    // { M(val) } -> std::same_as<M>;
};

// Concept for a type that has a "bind" operation
template <typename M, typename F>
concept HasBind = requires(M monad_instance, F func) {
    // Assumes bind operation takes a function and returns a new monad
    { monad_instance.bind(func) } -> std::same_as<M>;
};

// Combined concept for a Monadic type
template <typename M, typename T, typename F>
concept IsMonadic = HasUnit<M, T>&& HasBind<M, F>;

// Example usage:
struct MyIntMonad {
    int value;

    static MyIntMonad unit(int v) {
        return { v };
    }

    template <typename Func>
    MyIntMonad bind(Func f) const {
        return f(value);
    }
};

struct AnotherMonad {
    // Missing unit or bind
};

// A function that can be used with bind
MyIntMonad increment_and_wrap(int x) {
    return MyIntMonad::unit(x + 1);
}

static_assert(IsMonadic<MyIntMonad, int, std::function<MyIntMonad(int)> >, "MyIntMonad should be monadic");

//--------------------------------


struct MyOptionalInt {
    int number;
    bool isValid;
    MyOptionalInt() { isValid = false; number = 0; }
    MyOptionalInt(int num) { isValid = true; number = num; }
    bool IsValid() { return isValid; }
    int Value() { return number; }

    static MyOptionalInt unit(int v) { return MyOptionalInt(v); }
    template <typename Func>
    MyOptionalInt bind(Func f) const { return f(number); }
};
static_assert(IsMonadic<MyOptionalInt, int, std::function<MyOptionalInt(int)>>, "MyOptionalInt should be monadic");

MyOptionalInt divide_100_to(int x) {
    if (x == 0)
        return MyOptionalInt();
    return MyOptionalInt::unit(100 / x);
}



// static check of classes are they of 'IsMonadic' concept - in test_monadic_instances()...
