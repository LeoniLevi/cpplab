#pragma once


#include <concepts>
#include <type_traits>
#include <utility>
#include <functional>
#include <string>

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
concept IsMonadic00 = HasUnit<M, T>&& HasBind<M, F>;

// Example usage:
struct MyIntMonad00 {
    int value;

    static MyIntMonad00 unit(int v) {
        return { v };
    }

    template <typename Func>
    MyIntMonad00 bind(Func f) const {
        return f(value);
    }
};

struct AnotherMonad00 {
    // Missing unit or bind
};

// A function that can be used with bind
MyIntMonad00 increment_and_wrap(int x) {
    return MyIntMonad00::unit(x + 1);
}

static_assert(IsMonadic00<MyIntMonad00, int, std::function<MyIntMonad00(int)> >, "MyIntMonad should be monadic");

//--------------------------------

template <typename M, typename T, typename F>
concept IsMonadic = requires(T val, M monad_instance, F func) {
    { M::unit(val) } -> std::same_as<M>; 
    { monad_instance.bind(func) } -> std::same_as<M>;
};

template <typename T>
struct MyOptional {
    T value;
    bool isValid;
    MyOptional<T>() { isValid = false; value = T(); }
    MyOptional(T val) { isValid = true; value = val; }
    bool IsValid() { return isValid; }
    T Value() { return value; }

    static MyOptional<T> unit(T v) { return MyOptional<T>(v); }
    template <typename Func>
    MyOptional<T> bind(Func f) const { return isValid ? f(value) : MyOptional<T>(); }
};
static_assert(IsMonadic<
        MyOptional<int>, 
        int, 
        std::function< MyOptional<int>(int) >
    >, "MyOptional<int> should be monadic");

static_assert(IsMonadic<
        MyOptional<std::string>, 
        std::string, 
        std::function<MyOptional<std::string>(std::string)>
    >, "MyOptional<std::string> should be monadic");



// static check of classes are they of 'IsMonadic' concept - in test_monadic_instances()...
