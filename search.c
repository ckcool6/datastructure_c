#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_list.h"

int search_sq(SStable ST, KeyType key)
{
    int i;
    ST.elem[0].key = key; // 设置监视哨
    for (size_t i = ST.length; ST.elem[i].key != key; i--)
        ;
    return i;
}

int search_bin(SStable ST, KeyType key)
{
    int low = 1;
    int high = ST.length;

    while (low <= high)
    {
        int mid = low + high / 2;
        if (EQ(key, ST.elem[mid].key))
        {
            return mid;
        }
        else if (LT(key, ST.elem[mid].key))
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return 0;
}

/*动态查找*/

// 二叉排序树
Status search_bst(BinaryTree T, KeyType key, BinaryTree f, BinaryTree *p)
{
    if (!T)
    {
        p = f;
        return -1;
    }
    else if (EQ(key, T->data.key)) // 查找成功
    {
        p = T;
        return 1;
    }
    else if (LT(key, T->data.key))
    {
        return search_bst(T->Lchild, key, T, &p);
    }
    else
    {
        return search_bst(T->Rchild, key, T, &p);
    }
}

// 插入
Status insert_bst(BinaryTree *T, ElemType e)
{
    KeyType key;
    BinaryTree p;

    if (!search_bst(T, e.key, NULL, p))
    {
        BinaryTree s = (BinaryTree)malloc(sizeof(BinaryTreeNode));
        s->data = e;
        s->Lchild = s->Rchild = NULL;
        if (!p)
            T = s;
        else if (LQ(e.key, p->data.key))
        {
            p->Lchild = s;
        }
        else
        {
            p->Rchild = s;
        }
        return 1;
    }
    else
    {
        return -1;
    }
}

// 删除
Status delete(BinaryTree *p)
{
    if (!(*p)->Rchild)
    {
        BinaryTree q = p;
        p = (*p)->Lchild;
        free(q);
    }
    else if (!(*p)->Lchild)
    {
        BinaryTree q = p;
        p = (*p)->Rchild;
        free(q);
    }
    else // 左右子树均不为空
    {
        BinaryTree q = p;
        BinaryTree s = (*p)->Lchild;
        while (s->Rchild)
        {
            q = s;
            s = s->Rchild;
        } // 转左，然后向右走到头

        (*p)->data = s->data; // s指向被删节点的前驱

        if (q != p)
        {
            // 重接右子树
            q->Rchild = s->Lchild;
        }
        else
        { // 重接左子树
            q->Lchild = s->Lchild;
        }
        free(s);
    }
}

Status delete_bst(BinaryTree *T, KeyType key)
{
    if (!T)
    {
        return -1;
    }
    else
    {
        if (EQ(key, (*T)->data.key))
        {
            return delete (&T);
        }
        else if (LT(key, (*T)->data.key))
        {
            /* code */
            return delete_bst((*T)->Lchild, key);
        }
        else
        {
            return delete_bst((*T)->Rchild, key);
        }
    }
}

