#include <stdio.h>
#include <string.h>

int indexOf(char *str1, char *str2);

int main()
{
    char *target = "hello world again";
    char *tem = "world";
    printf("index:%d\n", indexOf(target, tem));

    char name[] = "zgh";
    printf("name is : %s,length:%d \n", name, strlen(name));

    char *fuk = "shanghai pudong new district";
    printf("address length:%d\n", strlen(fuk));

    //复制
    char copyname[10];
    strcpy(copyname, name);
    printf("copy name is : %s \n", copyname);

    //拼接
    char gugu[] = "hello ";
    //如果address是定长的，拼接时就会出现内存错误，为什么呢？
    //因为字符串实际是字符数组，结尾以\0结束
    //如果设置长度为5，结尾就不会自动加\0
    //这样拼接后结尾没有\0，不知道何处结尾，报错
    //基于以上原因，如果把长度设置为6，就能正常运行
    //所以后面必须要有结束标志
    // char address[5] = "world";
    char address[] = "world";
    printf("%d ,%d \n", sizeof(gugu), sizeof(address)); //7 6
    strcat(gugu, address);
    printf("%d ,%d \n", sizeof(gugu), sizeof(address)); //7 6
    printf("after cat : %s \n", gugu);

    return 0;
}


int indexOf(char *str1, char *str2)
{
    char *p = str1;
    int i = 0;
    p = strstr(str1, str2);
    if (p == NULL)
        return -1;
    else
    {
        while (str1 != p)
        {
            str1++;
            i++;
        }
    }
    return i;
}
