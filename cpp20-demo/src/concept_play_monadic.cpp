#include "concept_play_monadic.h"
#include "concept_monadic.h"

#include <print>

template<typename Coll>
void printCollection(const Coll& container) {
    std::print("{{");
    bool isfirst = true;
    for(auto const& elem: container) {
        if (isfirst)
            isfirst = false;
        else 
            std::print(", ");
        std::print("{0:.2f}", (double)elem);
    }
    std::print("}}");
}

void test_optional_monad() {    
    std::println(" ~~ test_optional_monad - started...");

    using optional_monad::pure;
    using optional_monad::operator |;

    std::optional<int> val0 = pure(10);

    auto result = 
        val0 | [](int x) { 
            return pure(x + 5); 
        } | [](int y) {
            if (y > 10) 
                return pure(y * 2);
            else 
                return std::optional<int>(); // Representing a "failure" or no value            
        };    

    if (result) {
        std::println(" -- Result: {}", *result);
    } else {
        std::println(" -- No result.");
    }

    std::optional<int> empty_value = std::nullopt;
    auto no_result = empty_value | [](int x) {
        return pure(x + 1);
    };

    if (no_result) {
        std::println(" -- This should not be printed.");
    } else {
        std::println(" -- No result from empty optional."); // Output: No result from empty optional.
    }

    std::println(" ~~ test_optional_monad - completed.");
}

void test_vector_monad() {    
    std::println(" ~~ test_vector_monad - started...");

    using vector_monad::pure;
    using vector_monad::operator |;

    std::vector<int> val0 { 10, 12, 15};

    auto result01 = val0 
        | [](int x) { 
            return pure(x + 5); 
        } | [](int y) {            
            return pure(y * 2);           
        };    

    std::print("Result01 is: ");
    printCollection(result01);  
    std::println();  

    auto result02 = val0 
        | [](int x) { 
            return pure(x + 5); 
        } | [](int y) {            
            return std::vector<int> { y * 2, y * 2};
        } | [](int x) { 
            return std::vector<double> { x / 0.98};
        };     

    std::print("Result02 is: ");
    printCollection(result02);  
    std::println();  
    
    std::println(" ~~ test_vector_monad - completed.");
}


bool test_monadic_instances() {
    static_assert(HasUnit<MyIntMonad, int>, "MyMonad should have a unit method for int");
    static_assert(HasBind<MyIntMonad, decltype(&increment_and_wrap)>, "MyMonad should have a bind method");
    static_assert(IsMonadic<MyIntMonad, int, decltype(&increment_and_wrap)>, "MyMonad should be monadic");

    // These will fail if uncommented, demonstrating compile-time checks
    // static_assert(HasUnit<AnotherMonad, int>, "AnotherMonad should have a unit method for int"); 
    // static_assert(HasBind<AnotherMonad, decltype(&increment_and_wrap)>, "AnotherMonad should have a bind method");
    // static_assert(IsMonadic<AnotherMonad, int, decltype(&increment_and_wrap)>, "AnotherMonad should be monadic");

    return true;
}
