#include <stdio.h>

typedef struct _MY_VECTOR *MY_VECTOR; //header

MY_VECTOR my_vector_init_default(void);

int my_vector_size(void);
int my_vector_capacity(void);

Status my_vector_push_back(MY_VECTOR hVector, int item);

void my_vector_destory(MY_VECTOR* pMY_VECTOR);
