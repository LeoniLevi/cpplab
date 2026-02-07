#include "myutil.h"

#include <vector>
#include <utility>
#include <stdio.h>
#include <time.h>
#include <functional>

void heapify(int arr[], int len);
void siftDown(int arr[], int len, int idx0);

void myheapsort(int items[], int len)
{
    heapify(items, len);
    int nlen = len;
    while (nlen > 1) {
        std::swap(items[0], items[nlen - 1]);
        siftDown(items, nlen - 1, 0);
        nlen -= 1;
    }
}


void test_myheapsort()
{
    //std::vector<int> myvect { 9, 6, 1, 7, 3, 5 };
    int numItems = 25;
    std::vector<int> myvect = get_random_int_data(numItems);
    int* items = myvect.data();

    printf(" ~~ source array:\n");
    print_ints(items, numItems);

    clock_t t00 = clock();
    myheapsort(items, numItems);
    clock_t t01 = clock();

    if (!is_array_asc_ordered(items, numItems)) {
        printf(" !! test_myheapsort(N=%d) - Incorrectly sorted !!\n", numItems);
        return;
    }

    //CLOCKS_PER_SEC
    long passedMs = (t01 - t00) * 1000 / CLOCKS_PER_SEC;
    printf(" ~~ Heapsort(N=%d) completed: %d millisecs\n", numItems, passedMs);

    printf(" ~~ after myheapsort:\n");
    print_ints(items, numItems);

}

//------------------

inline int leftChild(int idx)
{
    return idx * 2 + 1;
}

inline int rightChild(int idx)
{
    return idx * 2 + 2;
}

void siftDown(int arr[], int len, int idx0)
{
    int idx = idx0;
    while (idx < len) {

        int lt = leftChild(idx);
        int rt = rightChild(idx);

        int mci = -1;
        if (lt < len && rt < len)
            mci = arr[lt] > arr[rt] ? lt : rt;
        else if (lt < len)
            mci = lt;
        else if (rt < len)
            mci = rt;

        if (mci < 0)
            break;

        if (arr[mci] > arr[idx])
            std::swap(arr[idx], arr[mci]);
        idx = mci;        
    }
}

void heapify(int arr[], int len)
{
    for (int i = len / 2; i >= 0; --i) {
        siftDown(arr, len, i);
    }
}
