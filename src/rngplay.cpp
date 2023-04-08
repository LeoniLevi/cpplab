#include "rngplay.h"

#include <vector>
#include <ranges>
#include <span>

#include <algorithm>

#include <stdio.h>

namespace ranges = std::ranges;
namespace views = std::views;


void range_play()
{
	puts("\n === C++20 <RANGES> working example...");
	puts("---------------------");

	std::vector<int> ints = { 7, 12, 6, 9, 8, 5, 4 };

	std::span ss { &ints[1], 3 };
	printf(" span ss[1]: %d\n", ss[1]);

	auto even = [](int i) {return i % 2 == 0; };
	auto square = [](int i) { return i * i; };

	ranges::sort(ints);

	auto rints = ranges::reverse_view(ints);
	//auto rints = ranges::reverse(ints);

	for (int i : ints | views::reverse | views::filter(even) | views::transform(square)) {
		printf("%d, ", i);
	}
	putc('\n', stdout);

	//for (int i : views::transform(views::filter(rints, even), square)) {
	for (int i : ranges::transform_view(views::filter(rints, even), square)) {
		printf("%d; ", i);
	}
	putchar('\n');
}

/////////////////////
