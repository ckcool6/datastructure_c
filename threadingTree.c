#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef enum
{
    Link,
    Thread
} PointerTag; // link==0代表指针，thread==1代表线索

typedef struct
{
    void *data;
    struct BinaryThreadingTreeNode *lchid;
    struct BinaryThreadingTreeNode *rchid;
    PointerTag Ltag;
    PointerTag Rtag;

} BinaryThreadingTreeNode;

typedef BinaryThreadingTreeNode *BinaryThreadingTree;

// 双向链表
// 遍历线索二叉树
Status inorder_traverse_threading_tree(BinaryThreadingTree T, Status (*visit)(void *e))
{
    BinaryThreadingTree p = T->lchid; // p指向根节点

    while (p != T)
    {
        // 访问左子树
        while (p->Ltag == Link)
        {
            p = p->lchid;
        }

        // 访问左子树为空的节点
        if (!visit(p->data))
        {
            return -1;
        }

        // 访问后继节点
        while (p->Rtag == Thread && p->rchid != T)
        {
            p = p->rchid;
            visit(p->data);
        }

        p = p->rchid; // 头尾相接
    }

    return 0;
}

// 线索化 把树转化为线索二叉树
Status inorder_threading(BinaryThreadingTree *thrt, BinaryThreadingTree T)
{
    if (!((*thrt) = (BinaryThreadingTree)malloc(sizeof(BinaryThreadingTreeNode))))
    {
        return -1;
    }

    // 建头节点
    (*thrt)->Ltag = Link;
    (*thrt)->Rtag = Thread;

    // 右指针回指
    (*thrt)->rchid = thrt;
    // 若二叉树为空，则左指针回指
    if (!T)
    {
        (*thrt)->lchid = thrt;
    }
    else
    {
        (*thrt)->lchid = T;
        BinaryThreadingTree pre = thrt;

        inthreading(T); // 中序线索化

        pre->lchid = thrt;
        pre->Rtag = Thread; // 最后一个节点线索化

        (*thrt)->rchid = pre;
    }

    return 0;
}

void inthreading(BinaryThreadingTree p)
{
    BinaryThreadingTree pre;
    if (p)
    {
        // 左子树线索化
        inthreading(p->lchid);

        //前驱线索
        if (!p->lchid)
        {
            p->Ltag = Thread;
            p->lchid = pre;
        }

        //后继线索
        if (!pre->rchid)
        {
            p->Rtag = Thread;
            p->rchid = p;
        }

        //保持pre指向p的前驱
        pre = p;

        // 右子树线索化
        inthreading(p->rchid);
    }
}

