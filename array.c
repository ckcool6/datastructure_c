#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_ARRAR_DIM 8

typedef void *ElemType;
typedef int Status;

typedef struct Array
{
    /* data */
    ElemType *base; // 基地址
    int dim;
    int *bounds;    // 界地址
    int *constants; // 常量基地址

} Array;

Status init_array(Array *A, int dim, ...)
{

    if (dim < 1 || dim > MAX_ARRAR_DIM)
    {
        /* code */
        return -1;
    }

    A->dim = dim;
    A->bounds = (int *)malloc(dim * sizeof(int));

    if (!A->bounds)
        exit(0);

    int total_elem = 1; // 元素总数total_elem
    va_list ap;         // ap是参数列表数组

    //
    va_start(ap, dim);

    for (size_t i = 0; i < dim; i++)
    {
        /* code */
        A->bounds[i] = va_arg(ap, int); // 指针后移

        if (A->bounds[i] < 0)
        {
            /* code */
            return -2;
        }

        total_elem = total_elem * A->bounds[i];
    }

    va_end(ap);

    //
    A->base = (ElemType *)malloc(total_elem * sizeof(ElemType));
    if (!A->base)
        exit(0);

    A->constants = (int *)malloc(dim * sizeof(int));
    if (!A->constants)
        exit(0);

    A->constants[dim - 1] = 1;
    for (size_t i = dim - 2; i >= 0; i--)
    {
        /* code */
        A->constants[i] = A->constants[i + 1] * A->bounds[i + 1];
    }

    return 0;
}

Status destroy_array(Array *A)
{
    if (!A->base)
        exit(0);
    free(A->base);
    A->base = NULL;

    if (!A->bounds)
        exit(0);
    free(A->bounds);
    A->bounds = NULL;

    if (!A->constants)
        exit(0);
    free(A->constants);
    A->constants = NULL;

    return 0;
}

Status locate(Array A, va_list ap, int *off)
{
    off = 0;
    for (size_t i = 0; i < A.dim; i++)
    {
        /* code */
        int index = va_arg(ap, int);

        if (index < 0 || index >= A.bounds[i])
        {
            /* code */
            return -1;
        }

        off = off + A.constants[i] * index;
    }
    return 0;
}

Status value(Array A, ElemType *e, ...)
{
    va_list ap;
    va_start(ap, e);
    int res;
    int off;

    if ((res = locate(A, ap, &off)) <= 0)
    {
        /* code */
        return res;
    }

    e = *(A.base + off);
    return 0;
}

Status assign(Array *A, ElemType e, ...)
{
    va_list ap;
    va_start(ap, e);
    int res;
    int off;

    if ((res = locate(*A, ap, &off)) <= 0)
    {
        /* code */
        return res;
    }

    *(A->base + off) = e;

    return 0;
}

int main()
{
    printf("=======array-test========\n");    
}
