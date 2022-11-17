#include <errno.h>
#include <stdlib.h>
#include "coroutine_int.h"

void rs_init(struct rs *rs)
{
    rs->top = 0;
}

static inline unsigned int __stack_unused(struct rs *rs)
{
    return STACK_SIZE - rs->top;
}

// push
int rs_push(struct rs *rs, struct task_struct *task)
{
    if (!__stack_unused(rs))
        return -EAGAIN;

    rs->r[rs->top] = task;
    rs->top++;

    return 0;
}

// pop
struct task_struct *rs_pop(struct rs *rs)
{
    struct task_struct *task;

    if (!rs->top)
        return NULL;

    rs->top--;
    task = rs->r[rs->top];

    return task;
}
