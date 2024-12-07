
#include <stdio.h>
#include <string.h>



int main()
{
	puts("====== expr-demo app");

	printf(" ~~ __cplusplus: %uu\n", __cplusplus);



	printf("====== program 'expr-demo': Completed! To exit - click <Enter>:\n");
	{ char dummy[32]; fgets(dummy, sizeof dummy, stdin); }
	return 0;
}

