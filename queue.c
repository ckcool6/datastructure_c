#include <stdio.h>
#include <stdlib.h>

typedef void *ElemType;
typedef int Status;
typedef struct queue_node
{
    ElemType data;
    struct queue_node *next;
} queue_node;

typedef queue_node *queue_ptr;
typedef struct queue
{
    queue_ptr front;
    queue_ptr rear;
} queue;

Status init_queue(queue *Q)
{
    (*Q).front = (*Q).rear = (queue_ptr)malloc(sizeof(queue_node));

    if (!(*Q).front)
    {
        exit(-1);
    }

    return 0;
}

Status destroy_queue(queue *Q)
{
    while ((*Q).front)
    {
        (*Q).rear = (*Q).front->next;

        free((*Q).front);

        (*Q).front = (*Q).rear;
    }
}

Status enqueue(queue *Q, ElemType e)
{
    queue_ptr p;

    p = (queue_ptr)malloc(sizeof(queue_node));

    if (!p)
    {
        exit(-1);
    }

    p->data = e;
    p->next = NULL;

    // 插队
    (*Q).rear->next = p;
    // 尾指针指向p
    (*Q).rear = p;
}

Status dequeue(queue *Q, ElemType *e)
{
    queue_ptr p;

    if ((*Q).rear == (*Q).front)
    {
        exit(-1);
    }

    p = (*Q).front->next;
    *e = p->data;

    (*Q).front->next = p->next;

    
    if ((*Q).rear == p)
    {
        (*Q).rear = (*Q).front;
    }

    free(p);

    return 0;
}
