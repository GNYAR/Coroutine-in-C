#include <stdio.h>
#include "../src/coroutine_int.h"

int main(void)
{
    struct task_struct task[10];
    struct rs rs;
    struct task_struct *tmp;

    rs_init(&rs);
    for (int i = 0; i < 10; i++)
    {
        task[i].tfd = i;
        printf("push %d, return %d\n", i, rs_push(&rs, &task[i]));
    }

    for (int i = 0; i < 5; i++)
    {
        tmp = rs_pop(&rs);
        if (tmp)
            printf("pop %d\n", tmp->tfd);
        else
            printf("pop failed\n");
    }

    for (int i = 5; i < 10; i++)
    {
        printf("push %d, return %d\n", i, rs_push(&rs, &task[i]));
    }

    for (int i = 0; i < 10; i++)
    {
        tmp = rs_pop(&rs);
        if (tmp)
            printf("pop %d\n", tmp->tfd);
        else
            printf("pop failed\n");
    }

    return 0;
}
