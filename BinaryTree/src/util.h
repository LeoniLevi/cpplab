#pragma once

#include <vector>
#include <stdio.h>

#define ERR_EXIT(msg) { printf("ERROR(R-ABORT): %s; #%d, %s\n", (msg), __LINE__, __FILE__); abort(); }
#define RASSERT(condition, msg) { if (!(condition)) ERR_EXIT((msg)); }

std::vector<int> get_random_arr(int arr_len, int max_val);