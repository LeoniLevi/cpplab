#include "concept_play_monadic.h"
#include "concept_monadic.h"

#include <stdio.h>
#include <iostream>

template<typename Cont>
void printContainer(const Cont& container) {
    std::cout << "{";
    bool isfirst = true;
    for(auto const&  elem: container) {
        if (isfirst)
            isfirst = false;
        else 
            std::cout << ", ";
        std::cout << elem;
    }
    std::cout << "}";
}

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

void test_vector_monad() {    
    printf(" ~~ test_vector_monad - started...\n");

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

    printf("Result01 is: ");
    printContainer(result01);  
    printf("\n");      

    auto result02 = val0 
        | [](int x) { 
            return pure(x + 5); 
        } | [](int y) {            
            return std::vector<int> { y * 2, y * 2};
        } | [](int x) { 
            return std::vector<double> { x / 0.98};
        };     

    printf("Result02 is: ");
    printContainer(result02);  
    printf("\n");  
    
    printf(" ~~ test_vector_monad - completed.\n");
}