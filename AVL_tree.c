#include <stdlib.h>
#include <string.h>

typedef float KeyType;
typedef int KeyType;
typedef char *KeyType;
typedef void *InfoType;
typedef int Status;

typedef struct ElemType
{
    KeyType key;
    InfoType otherinfo;
} ElemType;

typedef struct BSTNode
{
    ElemType data;
    int bf; // 平衡因子
    struct BSTNode *Lchild;
    struct BSTNode *Rchild;
} BSTNode;

typedef BSTNode *BSTree;

const EH = 0;  // 等高
const LH = +1; // 左高
const RH = -1; // 右高

// 右旋
void R_rotate(BSTree *p)
{
    BSTree lc = (*p)->Lchild;  // lc根节点指向p的左子树
    (*p)->Lchild = lc->Rchild; // lc的右子树变为p的左子树
    // 右旋
    lc->Rchild = p;
    // p指向新的根节点
    p = lc;
}

// 左旋
void L_rotate(BSTree *p)
{
    BSTree rc = (*p)->Rchild;
    (*p)->Rchild = rc->Lchild; 
    //左旋
    rc->Lchild = p;
    p = rc;
}

