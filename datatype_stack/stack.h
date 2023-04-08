#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct stack_
{
   void          *data;
   size_t         size;
   struct stack_ *prev;
} stack_t;

enum
{
    STK_OK = 0,
    STK_WRONG_ARG,
    STK_NOT_ENOUGH_DATA,
    STK_MALLOC_FAILED
};

int    stack_push(      stack_t **stk, const void *data, size_t size);
int    stack_pop (      stack_t **stk,       void *data, size_t size);
int    stack_top (const stack_t  *stk,       void *data, size_t size);
size_t stack_size(const stack_t  *stk);

#endif
