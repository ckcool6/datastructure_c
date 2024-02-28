#include <stdio.h>
#include <stdlib.h>

const STACK_INIT_SIZE = 100;
const STACKINCREMENT = 10;

typedef void *ElemType;
typedef int Status;

typedef struct Stack
{
    ElemType *base;
    ElemType *top;
    int stackSize;
} Stack;

// 构造空栈
Status init_stack(Stack *S)
{
    (*S).base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));

    if (!(*S).base)
        exit(-1);

    (*S).top = (*S).base;
    (*S).stackSize = STACK_INIT_SIZE;

    return 0;
}

// 获取栈顶元素
Status get_top(Stack S, ElemType *e)
{
    if (S.top == S.base)
    {
        return -1;
    }

    *e = *(S.top - 1);
    return 0;
}

// 
Status push(Stack *S, ElemType e)
{
    // 如果栈满，就开辟新空间
    if ((*S).top - (*S).base >= (*S).stackSize)
    {
        (*S).base = (ElemType *)realloc((*S).base, ((*S).stackSize + STACKINCREMENT) * sizeof(ElemType));

        if (!(*S).base)
        {
            exit(-1);
        }

        (*S).top = (*S).base + (*S).stackSize;
        (*S).stackSize = (*S).stackSize + STACKINCREMENT;
    }

    *(S->top) = e;
    (S->top)++;

    return 0;
}

// 
Status pop(Stack *S, ElemType *e)
{
    if ((*S).top == (*S).base)
        return -1;

    (*S).top--;
    *e = *((*S).top);

    return 0;
};

Status is_StackEmpty(Stack S)
{
	if(S.top==S.base)
		return 1;
	else
		return -1;
} 

