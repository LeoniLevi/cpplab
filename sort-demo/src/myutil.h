#pragma once

#include <vector>
#include <functional>


void print_ints(int* items, size_t numItems);
std::vector<int> get_random_int_data(size_t numItems);
bool is_array_asc_ordered(int* items, size_t numItems);
bool run_sample_sort(const char* sortName, std::function<void(int*, int)> sortFun, size_t numItems);
