#include "fsplay.h"
#include "rngplay.h"
#include "coroplay.h"
#include "conceptplay.h"
#include "myqsort.h"

#include "Logger.h"

#include <stdio.h>
#include <string.h>

void hello()
{
	char buf[32] = { 0 };
	puts("Hello, World!");
	puts("What is your name?:");
    if (fgets(buf, sizeof buf, stdin) != nullptr)
		buf[strcspn(buf, "\n")] = '\0';
	printf("Hello, %s!\n", buf[0] ? buf : "Unknown");
}




int main()
{
	startLogging("example_app");

	bool run_hello = false;
	if (run_hello) {
		hello();
		logInfo(" ~~ hello: done");
	}

	bool run_myqsort = true;
	if (run_myqsort) {
		test_myqsort();
		logInfo(" ~~ test_myqsort: done");
	}

	//return 0;
#ifdef USE_CPP20_COROUTINES
	play_coroutines();
	logInfo(" ~~ play_coroutines: done");
#endif

#ifdef USE_CPP20_RANGES
	range_play();
	logInfo(" ~~ range_play: done");
#endif

#ifdef USE_CPP17_FILESYSTEM
	fsplay();
	logInfo(" ~~ fsplay: done");
#endif

	play_concepts();
	logInfo(" ~~ playconcepts: done");

	printf(" ~~ program 'example': Completed! To exit - click <Enter>:\n");
    {char dummy[32]; fgets(dummy, sizeof dummy, stdin); }
	return 0;
}
	
