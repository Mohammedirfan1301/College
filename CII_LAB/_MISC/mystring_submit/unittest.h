/*
 * Each unit test is defined by a structure of this type.
 */
typedef struct UnitTest
{
    // Test function to be run
    int             (* pfThisTest)(void);
    
    // Name of the test, to be displayed
    char *             pTestName;
} UnitTest;


/*
 * The test program must define an array of UnitTest structures, called
 * "tests"
 */
extern UnitTest         tests[];

/*
 * The test program must define the number of tests in the "tests" array
 */
extern int              numberOfTests;
