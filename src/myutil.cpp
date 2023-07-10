#include "myutil.h"

#include <time.h>

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