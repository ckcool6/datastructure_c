#include <stdio.h>
#include <stdlib.h>

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

