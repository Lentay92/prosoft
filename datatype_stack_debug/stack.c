#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

#define _D(lev, ...) if (lev <= stack_log_level) {printf(__VA_ARGS__);}

// TODO: set log level from stack_set_log_level
static int stack_log_level;

// TODO: add statistics print function
static size_t total_push;
static size_t total_pop;
static size_t total_alloc;
static size_t total_free;
static size_t total_head_alloc_fail;
static size_t total_data_alloc_fail;

void stack_set_log_level(int new_level)
{
    stack_log_level = new_level;
}

void stack_print_stat()
{
    if (stack_log_level >= 4)
    {
        printf("total_push: %d, total_pop: %d, total_alloc: %d, total_free: %d, total_head_alloc_fail: %d, total_data_alloc_fail: %d\n",
        total_push, total_pop, total_alloc, total_free, total_head_alloc_fail, total_data_alloc_fail);
    }
}

// TODO: add more debug outputs and statistics gathering
int stack_push(stack_t **stk, const void *data, size_t size)
{
    if (!stk || !data || !size)
    {
        _D(STK_D_WRN, "stack_push:: wrong arg: stk=%p, data=%p, size=%lu\n", stk, data, size);
        return STK_WRONG_ARG;
    }

    stack_t *head = (stack_t*)malloc(sizeof(stack_t));

    if (!head)
    {
        _D(STK_D_ERR, "stack_push:: failed to alloc stack head\n");
        total_head_alloc_fail++;
        return STK_MALLOC_FAILED;
    }

    total_alloc += sizeof(stack_t);
    total_push++;

    head -> data = malloc(sizeof *(head->data) * size);

    if (!(head -> data))
    {
        _D(STK_D_ERR, "stack_push:: failed to alloc stack data\n");
        total_data_alloc_fail++;
        return STK_MALLOC_FAILED;
    }

    memcpy(head->data, data, size);
    head -> size = size;
    head -> prev = *stk;
    *stk = head;

    stack_print_stat();

    return STK_OK;
}

int stack_top (const stack_t *stk, void *data, size_t size)
{
    if (!stk || !data)
    {
        _D(STK_D_WRN, "stack_top:: wrong arg: stk=%p, data=%p\n", stk, data);
        return STK_WRONG_ARG;
    }

    if (stk->size > size)
    {
        _D(STK_D_WRN, "stack_top:: not enough size in data: data=%p\n", data);
        return STK_NOT_ENOUGH_DATA;
    }

    memcpy(data, stk->data, stk->size);

    stack_print_stat();

    return STK_OK;
}

int stack_pop (stack_t **stk, void *data, size_t size)
{
    if (!stk)
    {
        _D(STK_D_WRN, "stack_push:: wrong arg: stk=%p\n", stk);
        return STK_WRONG_ARG;
    }

    stack_t *tmp = *stk;
    int result = stack_top(*stk, data, size);

    total_free += sizeof(tmp);
    total_pop++;

    if (result == STK_OK)
    {
        *stk = (*stk) -> prev;
        free(tmp -> data);
        free(tmp);
    }

    stack_print_stat();

    return result;
}

size_t stack_size (const stack_t *stk)
{
    size_t count = 0;

    while(stk)
    {
        stk = stk -> prev;
        count++;
    }

    _D(STK_D_DBG, "stack_size::stk=%p, size=%lu\n", stk, count);

    return count;
}
