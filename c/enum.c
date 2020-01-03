#include <stdio.h>

enum Week
{
    Mon,
    Tues,
    Wen,
    Thur,
    Fri,
    Sat,
    Sun
};

enum Color
{
    Red,
    Blue=10,
    Green,
    Black
};

int main()
{
    enum Week day;
    printf("------------test enum that continuous-------------- \n");
    //这个正常显示，打印七行
    for (day = Mon; day <= Sun; day++)
    {
        printf("day is : %d \n", day);
    }

    //这个就异常了，会打印出来13行，从0开始，直到13
    //因为Blue是10，后面从此开始++
    printf("------------test enum that not continuous-------------- \n");
    enum Color cl;
    for (cl = Red; cl <= Black; cl++)
    {
        printf("color is : %d \n", cl);
    }
    return 0;
}