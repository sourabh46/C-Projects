#include <stdio.h>
#include <string.h>

#include "CuTest.h"
#include "../../product/src/utility.c"

void TestLargestEvenSumOfKIntegers(CuTest *tc) 
{
    int A[5] = {4, 2, 6, 9, 8};
    int N = 5, K = 3;
    int actual = largestEvenSumOfKIntegers(A, N, K);
    int expected = 18;
    CuAssertIntEquals(tc, expected, actual);
}

void TestStrToUpper(CuTest *tc) 
{
    char* input = strdup("hello world");
    char* actual = strToUpper(input);
    char* expected = "HELLO WORLD";
    CuAssertStrEquals(tc, expected, actual);
}

void TestBinarySearch(CuTest *tc) 
{
    int A[5] = {2, 3, 6, 8, 9};
    int N = 5, X = 8;
    int actual = binarySearch(A, N, X);
    int expected = 3;
    CuAssertIntEquals(tc, expected, actual);
}

/*************************************************/
/* Test Suite for Utility functions (utility.c)  */
/*************************************************/

CuSuite* UtilityGetSuite()
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestLargestEvenSumOfKIntegers);
    SUITE_ADD_TEST(suite, TestStrToUpper);
    SUITE_ADD_TEST(suite, TestBinarySearch);

	return suite;
}