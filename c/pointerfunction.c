#include <stdio.h>

int sum(int x, int y)
{
    return x + y;
}

void sayHello()
{
    printf("hello, is that you who called me seconds ago? \n");
}

int main()
{
    //指针函数，指向函数，声明时也要声明参数列表和返回值类型
    //声明后可以与普通函数一样使用
    int (*p)(int, int) = &sum;
    printf("result is : %d \n", p(3, 4));

    //无参函数
    void (*pv)() = &sayHello;
    pv();
    return 0;
}