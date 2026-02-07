#include "myutil.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


bool run_sample_sort(const char* sortname, std::function<void(int*, int)> sortFun, size_t numItems)
{
	std::vector<int> myvect = get_random_int_data(numItems);
	int* items = myvect.data();

	clock_t t00 = clock();
	sortFun(items, numItems);
	clock_t t01 = clock();

	if (!is_array_asc_ordered(items, numItems)) {
		printf(" !! %s(N=%lld) - Incorrectly sorted !!\n", sortname, (long long)numItems);
		return false;
	}

	long millis = (t01 - t00) * 1000 / CLOCKS_PER_SEC;
	printf(" ~~ %s - Sort<N=%lld> done: took %d millisecs\n", sortname, (long long)numItems, millis);
	return true;
}

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
		int num = rand() % (numItems * 10);
		v.push_back(num);
	}
	return v;
}

bool is_array_asc_ordered(int* items, size_t numItems)
{
	for (size_t i = 1; i < numItems; ++i) {
		if (items[i] < items[i - 1])
			return false;
	}
	return true;
}