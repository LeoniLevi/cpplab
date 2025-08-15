#pragma once

#include <concepts>
#include <optional>
#include <functional>
#include <iostream>


template <template <typename> typename M, typename T>
concept Monad = requires(T val, M<T> m_val, auto func) {
    // Requirement for 'return' or 'unit' operation
    { M<T>::make_monadic(val) } -> std::same_as<M<T>>;

    // Requirement for 'bind' operation
    { m_val.and_then(func) } -> std::convertible_to<M<std::invoke_result_t<decltype(func), T>>>;
    // The exact return type and argument types for 'and_then' would depend on the specific monad implementation.
};


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

