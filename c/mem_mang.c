/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Karl Storz
 * @Date: 2019-10-10 15:54:54
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2019-10-10 16:49:06
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char name[100];
    char *description;

    strcpy(name, "Loki Zhao");

    description = (char *)malloc(100 * sizeof(char));
    if (description == NULL)
    {
        fprintf(stderr, "Error-unable to allocate required memory \n");
    }
    else
    {
        strcpy(description, "Here is a man who love his daughter more than everything \n");
    }
    printf("Name:%s \n", name);
    printf("Description: %s \n", description);
    //只有动态分配的内存才能free释放，name在定义时已指定长度，无法释放
    // free(name);
    free(description);

    return 0;
}