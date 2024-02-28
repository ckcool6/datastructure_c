typedef void *ElemType;
typedef int Status;

typedef struct Stack
{
    ElemType *base;
    ElemType *top;
    int stackSize;
} Stack;

Status init_stack(Stack *);

Status get_top(Stack, ElemType *);

Status push(Stack *, ElemType);

Status pop(Stack *, ElemType *);

Status is_StackEmpty(Stack);
