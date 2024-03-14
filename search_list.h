#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 关键字类型
typedef float KeyType;
typedef int KeyType;
typedef char *KeyType;
typedef void* InfoType;

// 宏定义及宏参数加括号是为了避免优先级的问题
//  对数值类关键字的比较
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

// 对字符串类关键字的比较
#define EQ(a, b) (!strcmp((a), (b)))
#define LT(a, b) (strcmp((a), (b)) < 0)
#define LQ(a, b) (strcmp((a), (b)) <= 0)

// 数据元素类型
typedef struct ElemType
{
    /* data */
    KeyType key;
    InfoType otherinfo;
} ElemType;

typedef struct SStable
{
    /* data */
    ElemType *elem;
    int length;

} SStable;

