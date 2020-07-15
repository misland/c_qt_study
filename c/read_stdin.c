/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-19 13:25:03
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-05-20 09:49:39
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *agrv)
{
    char buf[10];
    //都得到十个字节才会中断继续往下读，是不是有点蠢

    //只读一次，一次读十个字节，成功返回1
    // int count = fread(buf, 10, 1, stdin);
    //读十次，一次读一个字节，成功返回10
    // int count = fread(buf, 1, 10, stdin);
    // printf("count:%d,content:%s", count, buf);

    //如果是用char* result=NULL;result无法接收输入
    char *result[100];
    scanf("%s", result);
    printf("result:%s\n", result);
    return 0;
}
