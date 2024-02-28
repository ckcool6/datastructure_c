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

Status inorder_travese(BinaryTree T, Status (*visit)(ElemType))
{
    Stack S;
    BinaryTree p;

    init_stack(&S);
    push(&S, T);

    while (!is_StackEmpty(S))
    {
        // 左子树压栈
        while (get_top(S, &p) && p)
        {
            push(&S, p->Lchild);
        }

        // 否则，p为null的时候，退栈,然后右子树压栈
        pop(&S, &p);
        if (!is_StackEmpty(S))
        {
            pop(&S, &p);
            if (!visit(p->data))
            {
                return -1;
            }
            push(&S, p->Rchild);
        }
    }
    
    return 0;
}

