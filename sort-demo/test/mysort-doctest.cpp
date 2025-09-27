#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

struct MyArrFixture {
    int* intArrPtr;
    int  intArrLen;

    MyArrFixture() {
        intArrLen = 14;
        intArrPtr = new int[intArrLen] {22, 12, 17, 96, -24, -13, -19, 92, 54, -13, 3, 17, 55, 3};
    }
    ~MyArrFixture() {
        intArrLen = 0;
        delete[] intArrPtr;
    }
};

DOCTEST_TEST_CASE_FIXTURE(MyArrFixture, "test QSort using fixture") {
    myqsort(intArrPtr, intArrLen);
    for (int i = 1; i < intArrLen; ++i) {
        CHECK(intArrPtr[i] >= intArrPtr[i - 1]);
    }
}

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