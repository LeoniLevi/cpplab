#include "mymergesort.h"
#include "myutil.h"

#include <vector>
#include <assert.h>
#include <stdio.h>

void do_mergesort00(int arr[], size_t first, size_t last, int temp[]);
void do_mergesort(int arr[], size_t first, size_t len, int temp[]);


void mymergesort(int items[], int numItems)
{
	std::vector<int> varr(numItems);
	int* temp = varr.data();
	//do_mergesort00(items, 0, numItems - 1, temp);
	do_mergesort(items, 0, numItems, temp);
}
//-------------------
// 

void merge_two_blocks(int arr[], int first0, int len0, int len1, int temp[])
{
	int first1 = first0 + len0;

	size_t i1 = 0;
	size_t i2 = first0;
	size_t i3 = first1;

	while (i2 < first0 + len0 || i3 < first1 + len1) {
		if (i2 < first0 + len0 && i3 < first1 + len1) {
			if (arr[i2] <= arr[i3])
				temp[i1++] = arr[i2++];
			else
				temp[i1++] = arr[i3++];
		}
		else if (i2 >= first0 + len0)
			temp[i1++] = arr[i3++];
		else // if (i3 >= first1 + block_len)
			temp[i1++] = arr[i2++];
	}

	for (auto k = 0; k < i1; ++k) {
		arr[first0 + k] = temp[k];
	}
}

void do_mergesort(int arr[], size_t first, size_t len, int temp[])
{
	if (len <= 1)
		return;
	int len0 = len / 2;
	int len1 = len - len0;

	do_mergesort(arr, first, len0, temp);
	do_mergesort(arr, first + len0, len1, temp);
	merge_two_blocks(arr, first, len0, len1, temp);
}


// 
// param 'last' is an actual index of the last interval element
void do_mergesort00(int arr[], size_t first, size_t last, int temp[])
{
	//printf("-**-(%d..%d): ", (int)first, (int)last); 
	//print_ints(arr + first, last - first + 1);
	if (first < last) {
		size_t mid = (first + last) / 2;
		do_mergesort00(arr, first, mid, temp);
		do_mergesort00(arr, mid + 1, last, temp);

		// create one sorted block from two sorted subblocks: [first..mid] & [mid+1..last]
		
		//merge_two_blocks(arr, mid - first, first, temp);
		

		size_t i1 = 0;
		size_t i2 = first;
		size_t i3 = mid + 1;

		while (i2 <= mid || i3 <= last) {
			if (i2 <= mid && i3 <= last) {
				if (arr[i2] <= arr[i3])
					temp[i1++] = arr[i2++];
				else
					temp[i1++] = arr[i3++];
			}
			else if (i2 > mid)
				temp[i1++] = arr[i3++];
			else // if (i3 > last)
				temp[i1++] = arr[i2++];
		}


		// copy temp to arr
		//assert(i1 == last - first + 1);
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

	mymergesort(myvect.data(), (int) myvect.size());

	printf(" ~~ after my_merge_sort_arr:\n");
	print_ints(myvect.data(), myvect.size());
}
