#include <stdio.h>
#include <string.h>

int main()
{
    char name[] = "zgh";
    printf("name is : %s \n", name);

    //复制
    char copyname[10];
    strcpy(copyname, name);
    printf("copy name is : %s \n", copyname);

    //拼接
    char gugu[]="hello ";
    //如果address是定长的，拼接时就会出现内存错误，为什么呢？
    //因为字符串实际是字符数组，结尾以\0结束
    //如果设置长度为5，结尾就不会自动加\0
    //这样拼接后结尾没有\0，不知道何处结尾，报错
    //基于以上原因，如果把长度设置为6，就能正常运行
    //所以后面必须要有结束标志
    // char address[5] = "world";
    char address[] = "world";
    printf("%d ,%d \n",sizeof(gugu),sizeof(address));//7 6
    strcat(gugu, address);
    printf("%d ,%d \n",sizeof(gugu),sizeof(address));//7 6
    printf("after cat : %s \n", gugu);

    return 0;
}