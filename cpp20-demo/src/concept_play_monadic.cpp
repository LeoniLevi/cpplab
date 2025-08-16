#include "concept_play_monadic.h"
#include "concept_monadic.h"

#include <print>

template<typename Cont>
void printContainer(const Cont& container) {
    std::print("{{");
    bool isfirst = true;
    for(auto const & elem: container) {
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
        std::println(" -- Result: %d", *result);
        //std::cout << "Result: " << *result << std::endl; // Output: Result: 30
    } else {
        std::println(" -- No result.");
        //std::cout << "No result." << std::endl;
    }

    std::optional<int> empty_value = std::nullopt;
    auto no_result = empty_value | [](int x) {
        return pure(x + 1);
    };

    if (no_result) {
        std::println(" -- This should not be printed.");
        //std::cout << "This should not be printed." << std::endl;
    } else {
        std::println(" -- No result from empty optional."); // Output: No result from empty optional.
       // std::cout << "No result from empty optional." << std::endl; // Output: No result from empty optional.
    }

    std::println(" ~~ test_optional_monad - completed.");
}

void test_vector_monad() {    
    std::println(" ~~ test_vector_monad - started...");

    using vector_monad::pure;
    using vector_monad::operator |;

    //std::vector<int> val0 = pure(10);
    std::vector<int> val0 { 10, 12, 15};

    auto result01 = val0 
        | [](int x) { 
            return pure(x + 5); 
        } | [](int y) {            
            return pure(y * 2);           
        };    

    std::print("Result01 is: ");
    printContainer(result01);  
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
    printContainer(result02);  
    std::println();  
    
    std::println(" ~~ test_vector_monad - completed.");
}