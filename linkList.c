#include <stdio.h>
#include <stdlib.h>

typedef void *ElemType;
typedef int Status;

typedef struct LNode
{
    /* data */
    ElemType data;
    struct LNode *next;
} LNode;

typedef LNode *LinkList;

// 初始化链表
Status init_linklist(LinkList *L)
{
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    return 0;
};

// 修改
Status change_elem(LinkList L, int i, ElemType *e)
{
    LinkList p = L->next;
    int j = 1;

    while (p && j < i)
    {
        /* code */
        j++;
        p = p->next;
    }

    if (!p || j > i)
    {
        /* code */
        return -1;
    }

    *e = p->data;
    return 0;
}

// 查找
LNode *find_elem(LinkList *L, ElemType e)
{
    LinkList p = (*L)->next;
    while (p && p->data != e)
    {
        /* code */
        p = p->next;
    }
    return p;
}

// 插入
Status list_insert(LinkList *L, int i, ElemType e)
{
    LinkList p = *L;
    int j = 0;

    while (p && (j < i - 1))
    {
        /* code */
        p = p->next;
        j++;
    }

    if (!p || j > i - 1)
    {
        return -1;
    }

    LinkList s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 0;
}

// 删除
Status list_delete(LinkList *L, int i)
{
    LinkList p = *L;
    int j = 0;

    while ((p->next) && (j < i - 1))
    {
        /* code */
        p = p->next;
        j++;
    }

    if (!p || j > i - 1)
    {
        return -1;
    }

    LinkList q = p->next;
    p->next = q->next;
    free(q);
    return 0;
}

// 后插法
Status create_list(LinkList *L, int n)
{
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;

    for (int i = 0; i < n; i++)
    {
        ElemType tmp;
        LinkList q;

        if (scanf("%p", &tmp) == 1)
        {
            LinkList p = (LinkList)malloc(sizeof(LNode));
            p->data = tmp; // 录入数据
            q->next = p;   // 后插节点
            q = q->next;   // 指针后移
        }
        else
            return -1;
    }
}

int main(int argc, char *argv)
{
    LinkList L;
    int i;
    ElemType e;

    init_linklist(&L);
    printf("测试init\n");
}

