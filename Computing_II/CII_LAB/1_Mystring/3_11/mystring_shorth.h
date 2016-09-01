/*
MYSTRING opaque object interface
*/

#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>

typedef struct _MYSTRING *MYSTRING;

enum mystring_status {MYSTRING_STATUS_ERROR, MYSTRING_STATUS_SUCCESS};
typedef enum mystring_status MyString_Status;

#define MYSTRING_STARTING_CAPACITY     7

MYSTRING mystring_init_default(void);
MYSTRING mystring_init_c_string(const char * const c_string);
void mystring_destroy(MYSTRING* p_hString);
int mystring_size(MYSTRING hString);
int mystring_capacity(MYSTRING hString);
MyString_Status mystring_output(MYSTRING hString, FILE* out);
MyString_Status mystring_concatenate_c_string(MYSTRING hString, char * c_string);
MyString_Status mystring_concatenate_mystring(MYSTRING hStringDest, MYSTRING hStringSource);
MyString_Status mystring_truncate(MYSTRING hString, int newMaxLen);
MyString_Status mystring_push(MYSTRING hString, char ch);
char mystring_pop(MYSTRING hString);
char mystring_peek(MYSTRING hString);
char mystring_get(MYSTRING hString, int index);
MyString_Status mystring_put(MYSTRING hString, int index, char ch);
MYSTRING mystring_init_substring(MYSTRING hStringSource, int index, int length);
char * mystring_to_c_string(MYSTRING hString, char c_string_arr[], int arrSize);
MyString_Status mystring_input(MYSTRING hString,
                               FILE * hFile,
                			 int bIgnoreLeadingWhiteSpace,
                               int (* fTerminate)(char ch,
                                                  int * pbDiscardChar));

#endif /* MYSTRING */
