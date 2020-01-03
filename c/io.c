#include <stdio.h>

int main()
{
    int c;
    //接收一个字符，输出时会转成ASCII码
    // printf("input something:");
    // c = getchar();
    // printf("your input is:%d\n", c);

    //接收一个字符串
    // char str[100];
    // printf("input something again:");
    // gets(str);
    // printf("your input is:");
    // puts(str);

    //scanf，能接收多个输入，但是只接受指针类型参数
    char str[100];
    int i;
    printf("input something:");
    scanf("%s %d", str, &i);
    printf("your input is:%s,%d\n", str, i);

    return 0;
}