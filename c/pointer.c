#include <stdio.h>

int main()
{
    int var1 = 100;
    char var2[10];
    printf("address of var1 is : %#X, var2 is : %#X \n", &var1, &var2);

    int *p = &var1;
    *p = 200;
    printf("value of a is : %d \n", *p);

    //空指针，指向内存地址0
    int *ptr = NULL;
    printf("address of ptr is : %#X \n", ptr);

    int arr[4] = {1, 2, 3, 4};
    //对于数组而言，变量名本身就是首个元素的地址，所以赋值时不能用&，用了反而报错
    int *ptrArray = arr;
    for (int i = 0; i < 4; i++)
    {
        printf("display by variable name, %dth element is : %d \n", i + 1, arr[i]);
        printf("display by pointer, %dth element is :`%d \n", (i + 1), *(ptrArray + i));
    }
    
    return 0;
}