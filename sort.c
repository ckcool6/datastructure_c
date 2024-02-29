#include <stdlib.h>
#include "sqList.h"

/*
插入类
交换类
选择类
归并类
*/

/* 插入类 */
//  直接插入排序
void insert_sort(SqList *L)
{
    int j, i;

    for (i = 2; i < (*L).length; i++)
    {
        if ((*L).r[i].key < (*L).r[i - 1].key)
        {
            (*L).r[0] = (*L).r[i];     // 暂存在i[0]
            (*L).r[i] = (*L).r[i - 1]; // r[i-1]后移

            for (j = i - 2; (*L).r[0].key < (*L).r[j].key; j--)
            {
                (*L).r[j + 1] = (*L).r[j]; // 逐个后移
            }

            (*L).r[j + 1] = (*L).r[0]; // 插入正确位置
        }
    }
}

// 折半插入排序
void bi_insert_sort(SqList *L)
{
    int i, j, low, high;
    for (i = 2; i < (*L).length; i++)
    {
        (*L).r[0] = (*L).r[i];

        low = 1;
        high = i - 1;

        while (low <= high)
        {
            int m = (low + high) / 2;
            if ((*L).r[0].key < (*L).r[m].key)
            {
                high = m - 1;
            }
            else
                low = m + 1;
        }

        for (j = i - 1; j >= high + 1; j--)
        {
            (*L).r[j + 1] = (*L).r[j];
        }

        (*L).r[high + 1] = (*L).r[0];
    }
}

// 希尔排序 todo
void shell_insert()
{
}
