#pragma once

#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <vector>

#include "gtest/gtest.h"

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