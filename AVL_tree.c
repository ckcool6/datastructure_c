#include <stdlib.h>
#include <string.h>

typedef float KeyType;
typedef int KeyType;
typedef char *KeyType;
typedef void *InfoType;
typedef int Status;
typedef enum Boolean
{
    true = 1,
    false = -1
} Boolean;

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

//  对数值类关键字的比较
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

// 对字符串类关键字的比较
#define EQ(a, b) (!strcmp((a), (b)))
#define LT(a, b) (strcmp((a), (b)) < 0)
#define LQ(a, b) (strcmp((a), (b)) <= 0)

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
    // 左旋
    rc->Lchild = p;
    p = rc;
}

Status insert_AVL(BSTree *T, ElemType e, Boolean taller)
{
    // 插入新节点，让树长高
    if (!T)
    {
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->Rchild = (*T)->Lchild = NULL;
        (*T)->bf = EH; // 等高
        taller = true; // 长高
    }
    else
    {
        // 已存在和e相等的节点，不插入
        if (EQ(e.key, (*T)->data.key))
        {
            taller = false;
            return 0;
        }
        // 继续在T的左子树中搜索
        if (LT(e.key, (*T)->data.key))
        {
            if (!insert_AVL((*T)->Lchild, e, taller))
            {
                return 0; // 未插入
            }
            // 已插入到T的左子树，且左子树长高
            if (taller)
            {
                // 检查平衡度
                switch ((*T)->bf)
                {
                    // 左子树比右子树高，左平衡
                case LH:
                    left_balance(&T);
                    taller = false;
                    break;
                    // 左右子树等高，树增高
                case EH:
                    (*T)->bf = LH;
                    taller = true;
                    break;
                    // 右比左高，现在等高
                case RH:
                    (*T)->bf = EH;
                    taller = false;
                    break;
                }
            }
        }

        else
        { // 继续在右子树搜索
            if (!insert_AVL((*T)->Rchild, e, taller))
            {
                return 0; // 未插入
            }
            if (taller)
            {
                switch ((*T)->bf)
                {
                case LH:
                    (*T)->bf = EH;
                    taller = false;
                    break;

                case EH:
                    (*T)->bf = RH;
                    taller = true;
                    break;
                case RH:
                    right_balance(&T);
                    taller = false;
                    break;
                }
            }
        }
    }

    return 1;
}

// 左平衡
void left_balance(BSTree *T)
{
    BSTree lc = (*T)->Lchild;

    switch (lc->bf)
    {
    case LH:
        (*T)->bf = lc->bf = EH;
        R_rotate(&T); // 单右旋
        break;

    case RH:
        BSTree rd = lc->Rchild;
        switch (rd->bf)
        {
        case LH:
            (*T)->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            (*T)->bf = lc->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            lc->bf = LH;
            break;
        }

        rd->bf = EH;
        // 先左旋，再右旋
        L_rotate((*T)->Lchild);
        R_rotate(&T);
        break;
    }
}

void right_balance(BSTree *T)
{
    // todo
}
