#include <stdio.h>
#include "../coroutine.h"

/*
COROUTINE_DEFINE(job)
{
    VAR_DEFINE2(int, i, j);
    VAR_DEFINE3(double, k, l, m);
    ARRAY_DEFINE(int, arr, 20);
    cr_begin();
    cr_set(i, 1);
    cr_set(j, 2);
    cr_set(k, 2.2);

    cr_set(arr, 2, 4);
    printf("[@ job %d] %d %d\n", *(int *)args, cr_dref(i), cr_dref(j));

    cr_yield();

    cr_set(i, cr_dref(i) + 1);
    if (cr_dref(arr, 4) == 2)
        printf("array success\n");
    printf("[# job %d] %d %d\n", *(int *)args, cr_dref(i), cr_dref(j));
    if (cr_dref(k) == 2.2)
        printf("variable success\n");

    cr_end();
}
*/

COROUTINE_DEFINE(job)
{
    VAR_DEFINE(int, i);

    cr_begin();

    cr_set(i, 5);
    while (cr_dref(i) != 0)
    {
        int value = cr_dref(i);

        printf("[job %d] %d\n", *(int *)args, value);
        cr_set(i, value - 1);

        if (value == 3)
            cr_yield();
    }

    cr_end();
}

int main(void)
{
    int crfd, tfd[5];

    crfd = coroutine_create(CR_LIFO);
    if (crfd < 0)
        return crfd;

    for (int i = 0; i < 5; i++)
    {
        tfd[i] = i;
        printf("[tfd %d] %d added, %d\n", coroutine_add(crfd, job, &tfd[i]), i,
               tfd[i]);
    }

    coroutine_start(crfd);

    coroutine_join(crfd);
    return 0;
}
