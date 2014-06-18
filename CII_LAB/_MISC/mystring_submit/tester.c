/*
 * This is the main program to drive unit tests. It requires that there be a
 * linked file that contains the variable "tests", as defined in unittest.h
 */

#include <stdio.h>
#include "unittest.h"

int main(int argc, char * argv[])
{
    int             i;
    int             bFailed;
    int             bFoundFailure = 0;
    UnitTest *      pTest;
    
    // For each defined test...
    for (i = 0, pTest = &tests[0];
         i < numberOfTests;
         ++i, ++pTest)
    {
        // ... run that test and display the result.
        // Each test displays its particular error message.
        printf("Test %2d (%s):\n", i, pTest->pTestName);
        bFailed = (* pTest->pfThisTest)();
        printf("    %s\n",
               bFailed ? "FAIL" : "SUCCESS");
        
        // Keep track of whether we find any failures
        bFoundFailure = bFoundFailure || bFailed;
    }
    
    // Return 1 if we found a failure; 0 if there were no failures.
    return bFoundFailure;
}


