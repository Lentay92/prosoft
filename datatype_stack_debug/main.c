#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct
{
    int x;
    int y;
} Point;

int main(int argc, char **argv)
{
    if (argc > 1)
       stack_set_log_level(atoi(argv[1]));

    // int test
    stack_t *stk1 = NULL;

    int i = 0;
    stack_push(&stk1, &i, sizeof(i));
    i++;
    stack_push(&stk1, &i, sizeof(i));
    i++;
    stack_push(&stk1, &i, sizeof(i));
    printf("%lu\n", stack_size(stk1)); // 3

    int x = 123;
    stack_pop(&stk1, &x, sizeof(x));
    printf("%d, %lu more\n", x, stack_size(stk1)); // 2, 2 more
    stack_top(stk1, &x, sizeof(x));
    printf("%d, %lu more\n", x, stack_size(stk1)); // 1, 2 more
    //-------------------------------------------------------------
    // String test
    stack_t *stk2 = NULL;
    stack_push(&stk2, "Hello", sizeof("Hello"));
    stack_push(&stk2, "world", sizeof("world"));
    char s[256] = {0};
    stack_pop(&stk2, s, sizeof(s));
    printf("%s, %lu more\n", s, stack_size(stk2)); // world, 1 more
    stack_pop(&stk2, s, sizeof(s));
    printf("%s, %lu more\n", s, stack_size(stk2)); // Hello, 0 more
    //-------------------------------------------------------------
    // Struct test
    stack_t *stk3 = NULL;
    Point.x = 1;
    Point.y = 2;
    stack_push(&stk3, &Point, sizeof(Point));
    Point.x = 3;
    Point.y = 4;
    stack_push(&stk3, &Point, sizeof(Point));
    stack_pop(&stk3, &Point, sizeof(Point));
    int a = Point.x;
    int b = Point.y;
    printf("%d %d, %lu more\n", a, b, stack_size(stk3)); //3 4, 1 more
    stack_pop(&stk3, &Point, sizeof(Point));
    return 0;
}
