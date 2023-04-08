#include <stdlib.h>
#include <string.h>
#include "stack.h"

int stack_push(stack_t **stk, const void *data, size_t size)
{
    if (!stk || !data || !size)
        return STK_WRONG_ARG;

    stack_t *head = (stack_t*)malloc(sizeof(stack_t));

    if (!head)
        return STK_MALLOC_FAILED;

    head -> data = malloc(sizeof *(head->data) * size);

    if (!(head -> data))
        return STK_MALLOC_FAILED;

    memcpy(head->data, data, size);
    head -> size = size;
    head -> prev = *stk;
    *stk = head;

    return STK_OK;
}

int stack_top (const stack_t *stk, void *data, size_t size)
{
    if (!stk || !data)
        return STK_WRONG_ARG;

    if (stk->size > size)
        return STK_NOT_ENOUGH_DATA;

    memcpy(data, stk->data, stk->size);
    return STK_OK;
}

int stack_pop (stack_t **stk, void *data, size_t size)
{
    if (!stk)
        return STK_WRONG_ARG;

    stack_t *tmp = *stk;
    int result = stack_top(*stk, data, size);
    if (result == STK_OK)
    {
        *stk = (*stk) -> prev;
        free(tmp -> data);
        free(tmp);
    }
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

    return count;
}
