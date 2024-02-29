#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef void *ElemType;
typedef int Status;
typedef struct BinaryTreeNode
{
    ElemType data;
    struct BinaryTreeNode *Lchild;
    struct BinaryTreeNode *Rchild;
} BinaryTreeNode;

typedef BinaryTreeNode *BinaryTree;

void init_binaryTree(BinaryTree *T)
{
    *T = NULL;
}

Status create_binaryTree(BinaryTree *T)
{
    char ch;
    scanf(&ch);

    if (ch == '^')
    {
        *T = NULL;
    }
    else
    {
        *T = (BinaryTree)malloc(sizeof(BinaryTree));
        if (!(*T))
            exit(-1);
        (*T)->data = ch;
        create_binaryTree(&(*T)->Lchild);
        create_binaryTree(&(*T)->Rchild);
    }

    return 0;
}

Status print_element(ElemType e)
{
    printf(e);
    return 0;
}

Status preorder_traverse(BinaryTree T, Status (*visit)(ElemType))
{
    if (T)
    {
        if (visit(T->data))
        {
            if (preorder_traverse(T->Lchild, visit))
            {
                if (preorder_traverse(T->Rchild, visit))
                {
                    return 0;
                }
            }
        }
        else
            return -1;
    }
    else
    {
        return 0;
    }
}

Status inorder_travese(BinaryTree T)
{
    Stack S;
    BinaryTree p = T;
    BinaryTree q;

    init_stack(&S);
    q = (BinaryTree)malloc(sizeof(BinaryTreeNode));

    while (p || !is_StackEmpty(S))
    {
        if (p)
        {
            push(&S, p);   // 含有左子树的节点进栈
            p = p->Lchild; // 访问左子树
        }
        else
        {
            pop(&S, &q);     // 退栈
            printf(q->data); // 访问根节点
            p = q->Rchild;   // 访问右子树
        }
    }

    return 0;
}

void copy(BinaryTree T, BinaryTree *newT)
{
    if (T == NULL)
    {
        (*newT) = NULL;
        return;
    }

    else
    {
        (*newT) = (BinaryTree)malloc(sizeof(BinaryTreeNode));
        (*newT)->data = T->data;
        copy(T->Lchild, (*newT)->Lchild);
        copy(T->Rchild, (*newT)->Rchild);
    }
}

int depth(BinaryTree T)
{
    int m, n;

    if (T == NULL)
        return 0;
    else
    {
        m = depth(T->Lchild);
        n = depth(T->Rchild);

        if (m > n)
            return m + 1;
        else
            return n + 1;
    }
}

int count_node(BinaryTree T)
{
    if (T == NULL)
    {
        return 0;
    }

    else
    {
        return count_node(T->Lchild) + count_node(T->Rchild) + 1;
    }
}

