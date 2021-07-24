#include <stdbool.h>
#include <ctype.h>
#include "utility.h"

int largestEvenSumOfKIntegers(int *A, int N, int K)
{
    int index, pos, tmpVal, result;
    bool flag;
    /* Handle corner case - when array size is less than required number of integers */
    if (K > N)
        return -1;
    
    /* Sort the array of integers using insertion sort algorithm */
    for (index = 1; index < N; index++) 
    {  
        tmpVal = A[index];  
        pos = index - 1;  
  
        /* Move elements of A[0,...,index-1], that are  
        larger than tmpVal, to one position ahead  
        of their current position */
        while (pos >= 0 && A[pos] > tmpVal) 
        {  
            A[pos + 1] = A[pos];  
            pos = pos - 1;  
        }  
        A[pos + 1] = tmpVal;  
    }
    
    tmpVal = 0;
    /* Calculate sum of A[N-K,...,N-1] and hold inside tmpVal */
    for (index = N - K; index < N; index++)
        tmpVal += A[index];
    
    result = 0;
    /* If sum is odd */
    if (tmpVal % 2 != 0)
    {
        result = tmpVal; /* Store the current sum in result */
        for (index = N - K; index < N; index++)
        {
            flag = false;
            tmpVal = result;
            
            for (pos = N - K - 1; pos >= 0; pos--)
            {
                /* If the smallest of A[N-K,...,N-1] is odd and largest of A[0,...,N-K-1] is even */
                /* Or, if the smallest of A[N-K,...,N-1] is even and largest of A[0,...,N-K-1] is odd */
                /* Then raise the flag and break */
                if ((A[index] % 2 != 0 && A[pos] % 2 == 0) || (A[index] % 2 == 0 && A[pos] % 2 != 0))
                {
                    flag = true;
                    break;
                }
            }
            
            /* Adjust tmpVal (replace the smallest odd/even of A[N-K,...,N-1] by largest even/odd of A[0,...,N-K-1]) */
            if (flag == true)
            {
                tmpVal -= A[index];
                tmpVal += A[pos];
                break;
            }
        }
        if (flag == false)
            return -1;
        else
            result = tmpVal;
    }
    else
        result = tmpVal;
    
    return result;
}

char* strToUpper(char* str)
{
    char* p;
    for (p = str ; *p ; ++p) 
        *p = toupper(*p);
    
    return str;
}

int binarySearch(int *A, int N, int X)
{
    int right, mid, left;
    if (N == 0)
    {
        return -1;
    }
    left = 0;
    right = N - 1;
    while (left <= right) 
    {
        mid = (left + right) / 2;
        if (A[mid] >= X)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    if (A[left] == X)
    {
        return left;
    }
    return -1;
}
