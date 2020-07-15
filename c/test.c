/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-03-31 15:14:24
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-14 15:20:31
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main()
{
    FILE *fp = NULL;
    char *ptr;
    gcvt(1594710966.515913, 20, ptr);
    fp = fopen("test.txt", "wb+");
    fwrite(ptr, 1, strlen(ptr), fp);
    fclose(fp);
    return 0;
}