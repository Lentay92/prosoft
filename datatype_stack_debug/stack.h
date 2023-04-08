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

enum { // уровни лога
   STK_D_FTL = 0, // Fatal error
   STK_D_ERR = 1, // General error
   STK_D_WRN = 2, // Warning
   STK_D_INF = 3, // Information
   STK_D_DBG = 4  // Debug
};

typedef void (*stack_print_cb_t)(const stack_t *stk); // тип callback функции
void stack_print(const stack_t *stk, stack_print_cb_t print_cb); // для печати
void stack_set_log_level(int new_level); // установка уровня лога
void stack_print_stat(); // печать статистики


int    stack_push(      stack_t **stk, const void *data, size_t size);
int    stack_pop (      stack_t **stk,       void *data, size_t size);
int    stack_top (const stack_t  *stk,       void *data, size_t size);
size_t stack_size(const stack_t  *stk);

#endif
