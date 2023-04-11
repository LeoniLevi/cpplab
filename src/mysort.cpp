#include "mysort.h"

#include <vector>
#include <utility>
#include <span>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

void split_by_first(int items[], size_t beginIdx, size_t endIdx, size_t* last_less_eq_idx);

void print_ints(int* items, size_t numItems);

void mymerge(int arr[], size_t first, size_t last, int temp[])
{
	size_t mid = (first + last) / 2;

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


void mymergesort(int arr[], size_t first, size_t last, int temp[])
{
	//printf("-**-(%d..%d): ", (int)first, (int)last); 
	//print_ints(arr + first, last - first + 1);
	if (first < last) {
		size_t mid = (first + last) / 2;
		mymergesort(arr, first, mid, temp);
		mymergesort(arr, mid + 1, last, temp);

		mymerge(arr, first, last, temp);
	}
	//printf("-!!-(%d..%d): ", (int)first, (int)last); 
	//print_ints(arr + first, last - first + 1);
}

void my_merge_sort_arr(int items[], size_t numItems)
{
	std::vector<int> varr(numItems);
	int* temp = varr.data();
	mymergesort(items, 0, numItems - 1, temp);
}

//----------------

void myqsort1(int* items, size_t beginIdx, size_t endIdx)
{
	if (endIdx < beginIdx || endIdx - beginIdx < 2)
		return;
	size_t lastIdx = endIdx - 1;
	int pivot = items[lastIdx];
	size_t gtIdx = beginIdx; // gtIdx: is to be a first idx of greater-than-pivot element
	for (auto i = beginIdx; i < lastIdx; ++i) {
		if (items[i] < pivot) {
			std::swap(items[i], items[gtIdx]);
			gtIdx += 1;
		}
	}
	std::swap(items[gtIdx], items[lastIdx]);
	// now pivot element is in 'splitIdx' position
	myqsort1(items, beginIdx, gtIdx);
	myqsort1(items, gtIdx + 1, endIdx);
}

void myqsort_span(std::span<int> items)
{
	size_t len = items.size();
	if (len < 2)
		return;

	size_t lastIdx = len - 1;
	int pivot = items[lastIdx];
	size_t gtIdx = 0; // gtIdx: is to be a first idx of greater-than-pivot element
	for (auto i = 0; i < lastIdx; ++i) {
		if (items[i] < pivot) {
			std::swap(items[i], items[gtIdx]);
			gtIdx += 1;
		}
	}
	std::swap(items[gtIdx], items[lastIdx]);
	// now pivot element is in 'splitIdx' position

	//myqsort_span(items.subspan(0, gtIdx));
	//myqsort_span(items.subspan(gtIdx + 1, len - (gtIdx + 1)));
	
	//myqsort_span(std::span(items.begin(), items.begin() + gtIdx));
	//myqsort_span(std::span(items.begin() + gtIdx + 1, items.end()));	

	myqsort_span(items.first(gtIdx));
	myqsort_span(items.last(len - (gtIdx + 1)));

}

void myqsort_old(int* items, size_t beginIdx, size_t endIdx)
{
	if (endIdx <= beginIdx + 1) // if array empty or count=1
		return;

	size_t splitLastLeqIdx; // index of last less-or-equal item after splitting
	split_by_first(items, beginIdx, endIdx, &splitLastLeqIdx);

	// move(actually, swap) first, splitting item into 'splitIdx' position
	std::swap(items[beginIdx], items[splitLastLeqIdx]);

	// sort items before split-pos
	myqsort_old(items, beginIdx, splitLastLeqIdx);

	// sort items after split-pos (if any)
	myqsort_old(items, splitLastLeqIdx + 1, endIdx);
}



void split_by_first_00(int items[], size_t begin_idx, size_t end_idx, size_t* last_less_eq_idx)
{	
	int axis = items[begin_idx];
	size_t last_le_idx = begin_idx;
	size_t first_gt_idx = end_idx;

	for (size_t i = begin_idx + 1; i < end_idx; ++i) {
		if (items[i] <= axis) {
			if (first_gt_idx == end_idx) {
				last_le_idx = i;
			}
			else {
				std::swap(items[first_gt_idx], items[i]);
				last_le_idx = first_gt_idx;
				first_gt_idx += 1;
			}
		}
		else {
			if (first_gt_idx == end_idx) // not assigned yet
				first_gt_idx = i;
		}
	}
	*last_less_eq_idx = last_le_idx;
}

void split_by_first_01(int items[], size_t begin_idx, size_t end_idx, size_t* last_less_eq_idx)
{
	int axis = items[begin_idx];
	size_t last_le_idx = begin_idx;
	for (size_t i = begin_idx + 1; i < end_idx; ++i) {
		if (items[i] <= axis) {
			last_le_idx += 1;
			if (last_le_idx != i)
				std::swap(items[last_le_idx], items[i]);
		}
	}
	*last_less_eq_idx = last_le_idx;	

}

void split_by_first(int items[], size_t beginIdx, size_t endIdx, size_t* last_less_eq_idx)
{
	split_by_first_01(items, beginIdx, endIdx, last_less_eq_idx);
}

////////////////////////////////////

void print_ints(int* items, size_t numItems)
{
	printf("[");
	for (auto i = 0; i < numItems; ++i) {
		if (i > 0)
			printf(", ");
		printf("%d", items[i]);
	}
	printf("]\n");
}

std::vector<int> get_random_int_data(size_t numItems)
{
	std::vector<int> v;
	clock_t val = clock();
	//srand((unsigned)time(nullptr));
	srand((unsigned)val);

	for (auto i = 0; i < numItems; ++i) {
		int num = rand() % 100;
		v.push_back(num);
	}
	return v;
}


////////////////////////////////
void test_mymergesort()
{
	//std::vector<int> myvect { 9, 6, 1, 7, 3, 5 };
	std::vector<int> myvect = get_random_int_data(25);

	printf(" ~~ source array:\n");
	print_ints(myvect.data(), myvect.size());

	my_merge_sort_arr(myvect.data(), myvect.size());

	printf(" ~~ after my_merge_sort_arr:\n");
	print_ints(myvect.data(), myvect.size());
}

void test_myqsort()
{
	//std::vector<int> myvect { 9, 6, 1, 7, 3, 5 };
	std::vector<int> myvect = get_random_int_data(25);

	printf(" ~~ source array:\n");
	print_ints(myvect.data(), myvect.size());

	{
		
		int* items = myvect.data();
		size_t nitems = myvect.size();

		bool check_split = false;
		if (check_split) {
			size_t out_last_le_idx;
			split_by_first(items, 0, nitems, &out_last_le_idx);
			printf(" ~~ after split_by_first: out_last_le_idx=%d\n", (int)out_last_le_idx);
			print_ints(items, nitems);
		}


		myqsort_old(items, 0, nitems);
		printf(" ~~ after myqsort_old:\n");
		print_ints(items, nitems);
	}

	myvect = get_random_int_data(25);
	printf(" ~~ source array:\n");
	print_ints(myvect.data(), myvect.size());

	myqsort1(myvect.data(), 0, myvect.size());

	printf(" ~~ after myqsort1:\n");
	print_ints(myvect.data(), myvect.size());

	myvect = get_random_int_data(25);
	printf(" ~~ source array:\n");
	print_ints(myvect.data(), myvect.size());

	std::span ss{ myvect.data(), myvect.size() };
	myqsort_span(ss);

	printf(" ~~ after myqsort_span:\n");
	print_ints(myvect.data(), myvect.size());

}
