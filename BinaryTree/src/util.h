#pragma once

#include <vector>
#include <stdio.h>

#define ERR_EXIT(errmsg) { printf(" !! ERROR(R-ABORT): %s\n", (errmsg)); abort(); }
#define RASSERT(condition, errmsg) { if (!(condition)) ERR_EXIT((errmsg)); }

std::vector<int> get_random_arr(int arr_len, int max_val);