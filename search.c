#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_list.h"

int search_sq(SStable ST, KeyType key)
{
    int i;
    ST.elem[0].key = key; // 设置监视哨
    for (size_t i = ST.length; ST.elem[i].key != key; i--);
    return i;
}
