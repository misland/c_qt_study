#include <stdio.h>
#include <string.h>

//共同体，多个成员共同占用一块内存空间，同一时间只能有一个成员起作用
union Data {
    int i;
    float f;
    char str[20];
};

union Endian {
    char str;
    int data;
};

int main()
{
    union Data data;
    // union占用的内存空间是占用空间最多的那个元素
    printf("sizeof data is: %d\n", sizeof(data));

    data.i = 100;
    data.f = 3.1415;
    strcpy(data.str, "hello world");
    printf("i is: %d\n", data.i);
    printf("f is: %f\n", data.f);
    printf("str is: %s\n", data.str); //只有str正常输出，因为i和f都被str冲掉了

    data.i = 744;
    printf("i is: %d\n", data.i);
    data.f = 0.43;
    printf("f is: %f\n", data.f);
    strcpy(data.str, "hello again");
    printf("str is: %s\n", data.str); //这种方式一切正常

    //用来判断大小端
    union Endian test;
    test.data = 0x01020304;
    printf("char is:%#X\n", test.str); //01是小端，04是大端

    //也可以判断大小端
    int num = 1;
    char *a = (char *)&num;
    if (*a == 1)
    {
        printf("Little Endian");
    }
    else
    {
        printf("Big Endian");
    }

    return 0;
}
