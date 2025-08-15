#include "concept_play_monadic.h"
#include "concept_monadic.h"

#include <stdio.h>

void test_optional_monad() {    
    printf(" ~~ test_optional_monad - started...\n");

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
        printf(" -- Result: %d\n", *result);
        //std::cout << "Result: " << *result << std::endl; // Output: Result: 30
    } else {
        printf(" -- No result.\n");
        //std::cout << "No result." << std::endl;
    }

    std::optional<int> empty_value = std::nullopt;
    auto no_result = empty_value | [](int x) {
        return pure(x + 1);
    };

    if (no_result) {
        printf(" -- This should not be printed.\n");
        //std::cout << "This should not be printed." << std::endl;
    } else {
        printf(" -- No result from empty optional.\n"); // Output: No result from empty optional.
       // std::cout << "No result from empty optional." << std::endl; // Output: No result from empty optional.
    }

    printf(" ~~ test_optional_monad - completed.\n");
}