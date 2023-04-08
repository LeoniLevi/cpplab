#include "myqsort.h"

#include <vector>
#include <utility>
#include <span>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void split_by_first(int items[], size_t beginIdx, size_t endIdx, size_t* last_less_eq_idx);


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

void myqsort(int* items, size_t beginIdx, size_t endIdx)
{
	if (endIdx <= beginIdx + 1) // if array empty or count=1
		return;

	size_t splitLastLeqIdx; // index of last less-or-equal item after splitting
	split_by_first(items, beginIdx, endIdx, &splitLastLeqIdx);

	// move(actually, swap) first, splitting item into 'splitIdx' position
	std::swap(items[beginIdx], items[splitLastLeqIdx]);

	// sort items before split-pos
	myqsort(items, beginIdx, splitLastLeqIdx);

	// sort items after split-pos (if any)
	myqsort(items, splitLastLeqIdx + 1, endIdx);
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


		myqsort(items, 0, nitems);
		printf(" ~~ after myqsort:\n");
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
