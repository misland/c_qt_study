#include <stdio.h>
#include <stdlib.h>
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
  char *test;
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

//定义一个结构体，TestNode，并且将其命名为Node，
//之所以要再声明一个TestNode，因为结构体内部引用了自己，此时结构体还没有完成定义，是不能用Node的，所以要先声明一下，相当于一个临时名
//Node表示是结构体的名字，而pNode表示Node类型的指针，相当于int*
typedef struct TestNode
{
  int x, y;
  struct TestNode *pre;
  struct TestNode *next;
} Node, *pNode;

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

  pNode tnode = NULL;
  //这里会抛出TestNode未定义的错误，因为已经给TestNode取了别名：Node
  // printf("sizeof Node:%d\n", sizeof(TestNode));
  printf("sizeof pNode:%d\n", sizeof(pNode));//输出8
  printf("sizeof Node:%d\n", sizeof(Node));//输出24，两个int（8），两个指针（16）
  tnode = (pNode)malloc(sizeof(Node));

  return 0;
}