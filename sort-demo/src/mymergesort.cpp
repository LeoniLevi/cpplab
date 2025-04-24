#include "mymergesort.h"
#include "myutil.h"

#include <vector>
#include <assert.h>
#include <stdio.h>

void mergesort_using_temp(int arr[], size_t first, size_t last, int temp[]);

void mymergesort(int items[], int numItems)
{
	std::vector<int> varr(numItems);
	int* temp = varr.data();
	mergesort_using_temp(items, 0, numItems - 1, temp);
}
//-------------------

void mergesort_using_temp(int arr[], size_t first, size_t last, int temp[])
{
	//printf("-**-(%d..%d): ", (int)first, (int)last); 
	//print_ints(arr + first, last - first + 1);
	if (first < last) {
		size_t mid = (first + last) / 2;
		mergesort_using_temp(arr, first, mid, temp);
		mergesort_using_temp(arr, mid + 1, last, temp);

		// create one sorted block from two sorted subblocks

		size_t i1 = 0;
		size_t i2 = first;
		size_t i3 = mid + 1;

		while (i2 <= mid && i3 <= last) {
			if (arr[i2] < arr[i3])
				temp[i1++] = arr[i2++];
			else
				temp[i1++] = arr[i3++];
		}

		if (i2 <= mid) {
			while (i2 <= mid) {
				temp[i1++] = arr[i2++];
			}
		}
		else {
			assert(i3 <= last);
			while (i3 <= last)
				temp[i1++] = arr[i3++];
		}

		// copy temp to arr
		assert(i1 == last - first + 1);
		for (auto k = 0; k < i1; ++k) {
			arr[first + k] = temp[k];
		}
	}
	//printf("-!!-(%d..%d): ", (int)first, (int)last); 
	//print_ints(arr + first, last - first + 1);
}




//=======

void test_mymergesort()
{
	//std::vector<int> myvect { 9, 6, 1, 7, 3, 5 };
	std::vector<int> myvect = get_random_int_data(25);

	printf(" ~~ source array:\n");
	print_ints(myvect.data(), myvect.size());

	mymergesort(myvect.data(), myvect.size());

	printf(" ~~ after my_merge_sort_arr:\n");
	print_ints(myvect.data(), myvect.size());
}
