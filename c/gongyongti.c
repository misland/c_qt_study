#include <stdio.h>
#include <string.h>

struct
{
    unsigned int switch1;
    unsigned int switch2;
} status;

struct
{
    //变量后面跟长度，这种形式叫位域
    unsigned int degree1 : 1;
    unsigned int degree2 : 1;
} light;

struct
{
    unsigned int degree1 : 1;
    unsigned int degree2 : 1;
    unsigned int degree3 : 1;
    unsigned int degree4 : 1;
    unsigned int degree5 : 1;
    unsigned int degree6 : 1;
    unsigned int degree7 : 1;
    unsigned int degree8 : 1;
    unsigned int degree9 : 1;
    unsigned int degree10 : 1;
    unsigned int degree11 : 1;
    unsigned int degree12 : 1;
    unsigned int degree13 : 1;
    unsigned int degree14 : 1;
    unsigned int degree15 : 1;
    unsigned int degree16 : 1;
    unsigned int degree17 : 1;
    unsigned int degree18 : 1;
    unsigned int degree19 : 1;
    unsigned int degree20 : 1;
    unsigned int degree21 : 1;
    unsigned int degree22 : 1;
    unsigned int degree23 : 1;
    unsigned int degree24 : 1;
    unsigned int degree25 : 1;
    unsigned int degree26 : 1;
    unsigned int degree27 : 1;
    unsigned int degree28 : 1;
    unsigned int degree29 : 1;
    unsigned int degree30 : 1;
    unsigned int degree31 : 1;
    unsigned int degree32 : 1;
    unsigned int degree33 : 1;
} light2;

struct
{
    unsigned int age : 3;
} small;

int main()
{
    printf("size of status: %d \n", sizeof(status));
    //light的大小为4个字节
    light.degree1 = 1;
    printf("size of light: %d \n", sizeof(light));
    //light2的大小为8字节，因为声明了33个变量，已经超出了int类型的32bit，自动扩容了
    light2.degree1 = 1;
    printf("size of light2: %d \n", sizeof(light2));
    //age占3位，当赋值大于7时值会成0，无法保存，为什么不会自动扩容呢？
    //看来扩容与否不与变量内容有关，而是与实际变量数量有关的
    printf("size of small: %d \n", sizeof(small));
    small.age = 7;
    printf("age is: %d \n", small.age);//7
    small.age=8;
    printf("age is: %d \n", small.age);//0

    return 0;
}
