#include "fsplay.h"
#include "rngplay.h"
#include "coroplay.h"
#include "conceptplay.h"
#include "mysort.h"
#include "mymergesort.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

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

	puts("~~ RUN <my_print(5, \"mysval\", 'c');> :");
	my_print(5, "mysval", 'c');
	puts("~~ testing variadic template 'my_print': done");

	bool run_hello = false;
	if (run_hello) {
		hello();
		puts(" ~~ hello: done");
	}

	test_mymergesort();

	bool run_myqsort = true;
	if (run_myqsort) {
		test_myqsort();
		puts(" ~~ test_myqsort: done");
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
	
