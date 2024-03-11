#include <stdlib.h>
#include "sqList.h"
#include <stdbool.h>

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
        // 如果前面的元素比后面的小
        if ((*L).r[i].key < (*L).r[i - 1].key)
        {
            // 1.
            (*L).r[0] = (*L).r[i];     // 暂存在r[0]
            (*L).r[i] = (*L).r[i - 1]; // r[i-1]后移

            // 2.有序区从后往前扫描，逐个判断r[0]与有序区的每个元素
            for (j = i - 2; (*L).r[0].key < (*L).r[j].key; j--)
            {
                (*L).r[j + 1] = (*L).r[j]; // 逐个后移
            }

            // 3.
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

        (*L).r[0] = (*L).r[i]; // 暂存在r[0]

        low = 1;
        high = i - 1;

        // 2.扫描有序区，用二分查找法定位区间
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

        // 从被定位区间往后扫描
        for (j = i - 1; j >= high + 1; j--)
        {
            (*L).r[j + 1] = (*L).r[j];
        }

        (*L).r[high + 1] = (*L).r[0]; // 插入正确的位置
    }
}

// 希尔排序 缩小增量排序，分成子序列，每个子序列进行插入排序
void shell_insert(SqList *L, int dk)
{
    int i, j;
    // 对L进行增量为dk的插入排序
    for (i = dk + 1; i < (*L).length; i++)
    {
        // 如果前面的元素比后面的小
        if ((*L).r[i].key < (*L).r[i - dk].key)
        {
            (*L).r[0] = (*L).r[i]; // 暂存在r0

            // 从后往前扫描
            for (j = i - dk; j > 0 && (*L).r[0].key < (*L).r[j].key; j = j - dk)
            {
                (*L).r[j + dk] = (*L).r[j]; // 后移
            }

            (*L).r[j + dk] = (*L).r[0]; // 插入
        }
    }
}

void shell_sort(SqList *L, int dt[], int t)
{
    for (size_t k = 0; k < t; k++)
    {
        shell_insert(&L, dt[k]);
    }
}

/* 交换类 */

// 冒泡排序
void bubble_sort(SqList *L)
{
    int m = (*L).length - 1;
    bool flag = true; // 是否发生交换

    while ((m > 0) && (flag == true))
    {
        flag = false; // 没有发生交换的情况下，不会执行下一趟排序
        for (size_t j = 1; j <= m; j++)
        {
            if ((*L).r[j].key > (*L).r[j + 1].key)
            {
                RecordType t;

                flag = true; // 改为ture，表示发生了交换

                // 交换
                t = (*L).r[j];
                (*L).r[j] = (*L).r[j + 1];
                (*L).r[j + 1] = t;
            }
        }
        m--;
    }
}

// 快速排序
int partition(SqList *L, int low, int high)
{
    while (low < high)
    {
        // 设置基准
        (*L).r[0] = (*L).r[low];
        int pivotkey = (*L).r[low].key;

        // 比枢纽小的记录移动到低端
        while (low < high && (*L).r[high].key >= pivotkey)
        {
            --high;
        }
        (*L).r[low] = (*L).r[high];

        // 比枢纽大的记录移动到高端
        while (low < high && (*L).r[low].key <= pivotkey)
        {
            ++low;
        }
        (*L).r[high] = (*L).r[low];
    }

    //
    (*L).r[low] = (*L).r[0];
    return low;
}

void qsort(SqList *L, int low, int high)
{
    if (low < high)
    {
        int pivotloc = partition(&L, low, high);
        qsort(&L, low, pivotloc - 1);
        qsort(&L, pivotloc + 1, high);
    }
}

void quick_sort(SqList *L)
{
    qsort(&L, 1, L->length);
}

/*选择类*/

// 直接选择排序
void select_sort(SqList *L)
{
    for (size_t i = 1; i < (*L).length; i++)
    {
        int min_index = i;
        for (size_t j = i + 1; j <= (*L).length; j++)
        {
            if ((*L).r[j].key < (*L).r[min_index].key)
            {
                min_index = j; // 最小记录min_index指向j
            }
            if (min_index != i)
            {
                // 交换r[i]与r[min_index]
                RecordType temp = (*L).r[i];
                (*L).r[i] = (*L).r[min_index];
                (*L).r[min_index] = temp;
            }
        }
    }
}

/*树形选择排序*/

// 堆排序,最大的上浮，大根堆

void heap_adjust(SqList *L, int s, int m)
{
    RecordType parent = (*L).r[s];

    for (size_t j = 2 * s; j <= m; j = j * 2) // 纵向
    {
        if (j < m && (*L).r[j].key < (*L).r[j + 1].key) // 横向
        {
            j++;
        }

        if (parent.key >= (*L).r[j].key)
        {
            break;
        }

        (*L).r[s] = (*L).r[j]; // 交换父子节点
        s = j;
    }

    (*L).r[s] = parent;
}

// 创建大根堆
void create_heap(SqList *L)
{
    int n = (*L).length;

    for (size_t i = n / 2; i > 0; i--)
    {
        heap_adjust(&L, i, n);
    }
}

// 初建大根堆，反复交换堆顶和最后一个元素，重新调整堆
void heap_sort(SqList *L)
{
    create_heap(&L);

    for (size_t i = (*L).length; i > 1; i--)
    {
        // 将堆顶记录和当前未排序子序列[1..i]中最后一个记录互换
        RecordType x = (*L).r[1];
        (*L).r[1] = (*L).r[i];
        (*L).r[i] = x;

        // [1..i-1]重新调整为大根堆
        heap_adjust(&L, 1, i - 1);
    }
}

/*归并类*/

// 归并排序

// 子序列的归并
void merge(RecordType R[], RecordType T[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;

    // 将[low...mid]和[mid+1...high]并为[low...high]
    while (i <= mid && j <= high)
    {
        if (R[i].key <= R[j].key)
        {
            T[k++] = R[i++];
        }
        else
        {
            T[k++] = R[j++];
        }
    }

    while (i <= mid)
    {
        // 将剩余的R[i...mid]复制到T中,如果有的话
        T[k++] = R[i++];
    }

    while (j <= high)
    {
        ////将剩余的R[j...high]复制到T中，如果有的话
        T[k++] = R[j++];
    }
}

void msort(RecordType R[], RecordType T[], int low, int high)
{
    RecordType S[MAXSIZE+1];

    if (low == high)
    {
        T[low] = R[low];
    }

    else
    {
        int mid = (low + high) / 2;
        msort(R, S, low, mid);
        msort(R, S, mid + 1, high);
        merge(S, T, low, mid, high);
    }
}

void merge_sort(SqList *L)
{
    msort((*L).r, (*L).r, 1, (*L).length);
}

//基数排序
//todo