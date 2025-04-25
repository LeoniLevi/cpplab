#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("Testing myqsort function") {
    std::vector<int> varr = { 8, 2, 95, -12, 4, 45 };
    int sorted[] = { -12, 2, 4, 8, 45, 95 };
    int* items = varr.data();
    int numItems = (int)varr.size();

    myqsort(items, numItems);

    for (int i = 0; i < numItems; ++i) {
        CHECK(items[i] == sorted[i]);
    }
    CHECK(numItems == 6);
}