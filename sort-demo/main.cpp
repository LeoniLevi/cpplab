
#include "myqsort.h"
#include "mymergesort.h"
#include "myheapsort.h"

#include "myutil.h"

#include <iostream>
#include <fstream>



#include <stdio.h>
#include <string.h>
#include <algorithm>

void myStdSort(int items[], int len)
{
    std::sort(items, items + len, std::less<int>());
}




int main()
{
    puts("====== sort-demo app");

    printf(" ~~ __cplusplus: %lu\n", __cplusplus);


    //test_myheapsort();
    //run_sample_sort("myheapsort", myheapsort, 10000);
    run_sample_sort("myheapsort", myheapsort, 100000);
    run_sample_sort("myheapsort", myheapsort, 1000000);

    //run_sample_sort("myqsort", myqsort, 10000);
    run_sample_sort("myqsort01", myqsort01, 100000);
    run_sample_sort("myqsort01", myqsort01, 1000000);
    //run_sample_sort("myqsort", myqsort, 10000000);

    //run_sample_sort("myqsort00", myqsort00, 10000);
    run_sample_sort("myqsort00", myqsort00, 100000);
    run_sample_sort("myqsort00", myqsort00, 1000000);

    //run_sample_sort("mymergesort", mymergesort, 10000);
    run_sample_sort("mymergesort", mymergesort, 100000);
    run_sample_sort("mymergesort", mymergesort, 1000000);
    //run_sample_sort("mymergesort", mymergesort, 10000000);


    //run_sample_sort("myStdSort", myStdSort, 10000);
    run_sample_sort("myStdSort", myStdSort, 100000);
    run_sample_sort("myStdSort", myStdSort, 1000000);

    //test_mymergesort();

    //test_myqsort();

    printf("====== program 'sort-demo': Completed! To exit - click <Enter>:\n");
    {char dummy[32]; fgets(dummy, sizeof dummy, stdin); }
    return 0;
}
    
