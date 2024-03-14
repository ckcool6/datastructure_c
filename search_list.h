#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 关键字类型
typedef float KeyType;
typedef int KeyType;
typedef char *KeyType;

// 数据元素类型
typedef struct SElemType
{
    /* data */
    KeyType key;
    // 各种字段...
    char *name;
    int age;
    char *sex;
} SElemType;

// 对数值类关键字的比较
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

// 对字符串类关键字的比较
#define EQ(a, b) (!strcmp((a), (b)))
#define LT(a, b) (strcmp((a), (b)) < 0)
#define LQ(a, b) (strcmp((a), (b)) <= 0)

typedef struct SStable
{
    /* data */
    void *elem;
    int length;

} SStable;
