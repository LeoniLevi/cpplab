#include "util.h"

#include <algorithm>
#include <time.h>
#include <stdlib.h>

std::vector<int> get_random_arr(int arr_len, int max_val)
{
	std::vector<int> numbers;
	int maxNum = max_val;
	unsigned  nseed = (unsigned)time(NULL);
	srand(nseed);
	for (int i = 0; i < arr_len; ++i) {
		int num = rand() % maxNum;
		while (std::find(numbers.begin(), numbers.end(), num) != numbers.end()) {
			num = rand() % maxNum;
		}
		numbers.push_back(num);
	}
	return numbers;
}