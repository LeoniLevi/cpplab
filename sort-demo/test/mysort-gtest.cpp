//#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

#include "gtest/gtest.h"


class MyArrFixture : public testing::Test {
protected:
    int* intArrPtr;
    int  intArrLen;

    void SetUp() override {
        intArrLen = 14;
        intArrPtr = new int[intArrLen] {22, 12, 17, 96, -24, -13, -19, 92, 54, -13, 3, 17, 55, 3};
    }
    void TearDown() override {
        intArrLen = 0;
        delete[] intArrPtr;
    }
};

TEST_F(MyArrFixture, TestQSorting) {
    myqsort(intArrPtr, intArrLen);
    for (int i = 1; i < intArrLen; ++i) {
        EXPECT_GE(intArrPtr[i], intArrPtr[i - 1]);
    }
}


TEST(QSortTest, Simple) {
    std::vector<int> varr = { 8, 2, 95, -12, 4, 45 };
    int sorted[] = { -12, 2, 4, 8, 45, 95 };
    int* items = varr.data();
    int numItems = (int) varr.size();

    myqsort(items, numItems);

    for (int i = 0; i < numItems; ++i) {
        EXPECT_EQ(items[i], sorted[i]);
    }
    EXPECT_EQ(numItems, 6);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}