#include <stdio.h>
#include "utility.h"

int main()
{
    int A[5] = {4, 2, 6, 9, 8};
    int N = 5, K = 3, result = -1;

    result = largestEvenSumOfKIntegers(A, N, K);

    if(result == -1)
        printf("Result not found!\n");
    else
        printf("Result: %d\n", result);
    
    return 0;
}