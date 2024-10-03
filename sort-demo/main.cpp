
#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include <iostream>
#include <fstream>



#include <stdio.h>
#include <string.h>



int main()
{
	puts("====== sort-demo app");

	printf(" ~~ __cplusplus: %uu\n", __cplusplus);


	test_myheapsort();

	test_mymergesort();

	bool run_myqsort = true;
	if (run_myqsort) {
		test_myqsort();
		puts(" ~~ test_myqsort: done");
	}

	printf("====== program 'sort-demo': Completed! To exit - click <Enter>:\n");
    {char dummy[32]; fgets(dummy, sizeof dummy, stdin); }
	return 0;
}
	
