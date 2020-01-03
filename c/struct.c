#include <stdio.h>
#include <string.h>

//既声明了标签Books，也声明了变量名
//在这种方式下，能直接赋值
struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id
} book = {"C Programming", "Unkown", "None", 100};

//只声明了标签
//这种Person可以当作一种类型来声明变量，下面的不可以
struct Person
{
    //声明指针时不会为指针分配内存空间
    //所以在声明成员时，如果使用下面的方式
    //在为其赋值时虽然编译没问题，但是运行时就会出问题
    char* test;
    //这样才可以
    char name[50];
    char address[200];
    int age;
    char sex[5];
};

//这种等于只是声明了一个变量，无法用Person再声明变量
struct 
{
    char *name;
    char *address;
} Person;


//用typedef关键字声明
typedef struct
{
    int age;
    double money;
} assets;

int main()
{
    printf("size of struct is : %d \n", sizeof(book));
    //输出16，内存对齐原因，int也分配了8个字节的空间
    printf("size of struct is : %d \n", sizeof(assets));
    printf("name of book is : %s \n", book.title);

    struct Books bk;
    strcpy(bk.title, "C#");
    printf("name of bk is : %s \n", bk.title);

    struct Person ps;
    //会抛出异常
    // strcpy(ps.test,"hello world");
    strcpy(ps.name, "zgh");
    ps.age = 29;
    printf("name of ps is : %s,age is : %d \n", ps.name, ps.age);

    return 0;
}