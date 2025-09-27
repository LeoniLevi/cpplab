#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

//#include <catch2/catch_all.hpp>
#include <extras/catch_amalgamated.hpp>


struct MyArrFixture {
    int* intArrPtr;
    int  intArrLen;

    MyArrFixture()  {
        intArrLen = 14;
        intArrPtr = new int[intArrLen] {22, 12, 17, 96, -24, -13, -19, 92, 54, -13, 3, 17, 55, 3};
    }
    ~MyArrFixture() {
        intArrLen = 0;
        delete[] intArrPtr;
    }
};

TEST_CASE_METHOD(MyArrFixture, "test QSort using the fixture") {
    myqsort(intArrPtr, intArrLen);
    for (int i = 1; i < intArrLen; ++i) {
        REQUIRE(intArrPtr[i] >= intArrPtr[i - 1]);
    }
}

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