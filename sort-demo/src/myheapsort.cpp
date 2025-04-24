#include "myutil.h"

#include <vector>
#include <utility>
#include <stdio.h>

int leftChild(int idx)
{
    return idx * 2 + 1;
}

int rightChild(int idx)
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

/////

void test_myheapsort()
{
    //std::vector<int> myvect { 9, 6, 1, 7, 3, 5 };
    std::vector<int> myvect = get_random_int_data(25);

    printf(" ~~ source array:\n");
    print_ints(myvect.data(), myvect.size());

    myheapsort(myvect.data(), (int)myvect.size());

    printf(" ~~ after myheapsort:\n");
    print_ints(myvect.data(), myvect.size());
}