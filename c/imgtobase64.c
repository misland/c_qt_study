/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Karl Storz
 * @Date: 2020-01-06 13:16:15
 * @LastEditors  : Loki Zhao
 * @LastEditTime : 2020-01-06 14:39:27
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

#define MAX_LEN 10 * 1024 * 1024
// int base64_encode(char *out, const unsigned char *in, int inlen, int maxlen);

// 将图片转为base64编码
// 核心文件base64.h文件是从CSDN上摘的，链接如下：https://blog.csdn.net/superbfly/article/details/53168976
int main()
{
    char *out = malloc(MAX_LEN);
    FILE *file = fopen("/home/loki/me/study/C/demo/demo.jpg", "rb");
    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char *)malloc(len + 1);
    memset(content, 0, len + 1);
    fread(content, len, 1, file);
    printf("len:%ld \n", len);

    // char *content = "hello world";
    // printf("len:%ld \n", strlen(content));
    base64_encode(out, content, len, MAX_LEN);
    printf("%s \n", out);

    return 0;
}