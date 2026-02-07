#pragma once

#include <concepts>
#include <optional>
#include <vector>
#include <ranges>
#include <functional>
#include <string>

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



