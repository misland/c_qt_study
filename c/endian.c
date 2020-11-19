#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// length of num:4
// tem:78
// tem:56
// tem:34
// tem:12
//以上是windows下打印结果，内存低位存放的是数字的低位
//由于是int，占了4个字节，打印结果第一二三四个字节存放的是78、56、34、12
//所以windows中数据存放格式是小端，即低位存放在内存的低地址中
int main(int argc, char *argv)
{
    int num = 0x12345678;
    printf("length of num:%d\n", sizeof(num));
    for (int i = 0; i < sizeof(num); i++)
    {
        char tem = *((char *)&num + i);
        printf("tem:%x\n", tem);
    }
    return 0;
}