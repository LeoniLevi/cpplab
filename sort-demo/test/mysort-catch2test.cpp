#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

//#include <catch2/catch_all.hpp>
#include <extras/catch_amalgamated.hpp>

TEST_CASE("Testing myqsort function", "Simplest") {
    std::vector<int> varr = { 8, 2, 95, -12, 4, 45 };
    int sorted[] = { -12, 2, 4, 8, 45, 95 };
    int* items = varr.data();
    int numItems = (int)varr.size();

    myqsort(items, numItems);

    for (int i = 0; i < numItems; ++i) {
        REQUIRE(items[i] == sorted[i]);
    }
    REQUIRE(numItems == 6);
}