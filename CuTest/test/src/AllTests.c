#include <stdio.h>

#include "CuTest.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();
CuSuite* UtilityGetSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetSuite());
	CuSuiteAddSuite(suite, CuStringGetSuite());
	CuSuiteAddSuite(suite, UtilityGetSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main()
{
	RunAllTests();
    return 0;
}
