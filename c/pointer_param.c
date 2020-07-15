/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-18 17:24:28
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-05-18 17:35:05
 */
#include <stdio.h>
#include <stdlib.h>

int sum(int *param);

int main(int argc, char *argv[])
{
    int a = 34;
    int *p = &a;
    printf("sum:%d\n", sum(p));
    printf("a:%d\n", a);
    // system("pause");
    return 0;
}

int sum(int *param)
{
    printf("param:%d\n", *param);
    (*param)++;
    return 5 + *param;
}