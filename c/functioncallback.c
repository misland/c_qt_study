#include <stdio.h>
#include <stdlib.h>

int getRandom()
{
    return rand();
}

//第三个参数声明了一个指针函数，在C中称为回调
//看起来好像没什么特别的，但是肯定没这么简单，只是因为自己还很菜没见过世面而已
void getArray(int *arr, size_t size, int (*p)())
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = p();
    }
}

int main()
{
    int arr[10];
    //因为getRandom的参数列表和返回值与getArray中声明的一致，所以这里可以直接把其传入作为参数
    getArray(arr, 10, getRandom);
    for (int i = 0; i < 10; i++)
    {
        printf("%dth element is : %d \n", (i + 1), arr[i]);
    }

    return 0;
}