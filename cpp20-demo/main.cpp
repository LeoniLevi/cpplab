#include "fsplay.h"
#include "rngplay.h"
#include "coroplay.h"
#include "conceptplay.h"

//#include "myqsort.h"
//#include "mymergesort.h"
//#include "myheapsort.h"

#include <iostream>
#include <fstream>



#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
#   include <print>
#	include <expected>
#	include <iomanip>

enum class parse_error
{
	invalid_input,
	overflow
};

auto parse_number(std::string_view& str) -> std::expected<double, parse_error>
{
	const char* begin = str.data();
	char* end;
	double retval = std::strtod(begin, &end);

	if (begin == end)
		return std::unexpected(parse_error::invalid_input);
	else if (std::isinf(retval))
		return std::unexpected(parse_error::overflow);

	str.remove_prefix(end - begin);
	return retval;
}

void test_expected()
{
	puts(" === test_expected - Started...");

	auto process = [](std::string_view str)
		{
			std::cout << "str: " << std::quoted(str) << ", ";
			if (const auto num = parse_number(str); num.has_value())
				std::cout << "value: " << *num << '\n';
			// If num did not have a value, dereferencing num
			// would cause an undefined behavior, and
			// num.value() would throw std::bad_expected_access.
			// num.value_or(123) uses specified default value 123.
			else if (num.error() == parse_error::invalid_input)
				std::cout << "error: invalid input\n";
			else if (num.error() == parse_error::overflow)
				std::cout << "error: overflow\n";
			else
				std::cout << "unexpected!\n"; // or invoke std::unreachable();
		};

	for (auto src : { "42", "42abc", "meow", "inf" })
		process(src);

	puts(" === test_expected - Completed...");
}

#endif

//template <typename... TArgs>
//void my_print(TArgs... args);

void my_print()
{
	std::cout << "\n";
}

template<typename T, typename... TArgs>
void my_print(T arg, TArgs... args)
{
	std::cout << arg << " ";
	my_print(args...);
}

void hello()
{
	char buf[32] = { 0 };
	puts("Hello, World!");
	puts("What is your name?:");
    if (fgets(buf, sizeof buf, stdin) != nullptr)
		buf[strcspn(buf, "\n")] = '\0';
	printf("Hello, %s!\n", buf[0] ? buf : "Unknown");
}

void test_file()
{
	std::ofstream of("cucu.txt");
	int n = 5;
	of << "First Line: n=" << n << "\n";
	of << "Second Line: n*n=" << n * n;
}



int main()
{
	puts("====== CPP-Example app");

	printf(" ~~ __cplusplus: %uu\n", __cplusplus);

#if defined(_MSC_VER) && !defined(__clang__)
	printf(" ~~ _MSVC_LANG: %d\n", (int)_MSVC_LANG);
	printf(" ~~ _MSC_VER: %d\n", (int)_MSC_VER);

	std::println("sum of {} and {} is {}", 5, 4, 5 + 4);
	test_expected();

#elif defined(__GNUC__)
	printf(" ~~ __GNUC__: %d\n", (int)__GNUC__);
	printf(" ~~ __GNUC_MINOR__: %d\n", (int)__GNUC_MINOR__);
	printf(" ~~ __GNUC__: %d\n", (int)__GNUC__);
#endif

	puts("~~ RUN <my_print(5, \"mysval\", 'c');> :");
	my_print(5, "mysval", 'c');
	puts("~~ testing variadic template 'my_print': done");

	bool run_hello = false;
	if (run_hello) {
		hello();
		puts(" ~~ hello: done");
	}


	//return 0;
	//
#ifdef USE_CPP20_COROUTINES
	play_coroutines();
	puts(" ~~ play_coroutines: done");
#endif

#ifdef USE_CPP20_RANGES
	range_play();
	puts(" ~~ range_play: done");
#endif

#ifdef USE_CPP17_FILESYSTEM
	fsplay();
	puts(" ~~ fsplay: done");
#endif

	play_concepts();
	puts(" ~~ playconcepts: done");

	printf("====== program 'CPP-Example': Completed! To exit - click <Enter>:\n");
    {char dummy[32]; fgets(dummy, sizeof dummy, stdin); }
	return 0;
}
	
