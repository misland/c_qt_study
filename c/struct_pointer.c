#include <stdio.h>
#include <string.h>

struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

void printBook(struct Books *book);

int main()
{
    struct Books bk1;
    struct Books bk2;

    strcpy(bk1.title, "Hello World");
    strcpy(bk1.author, "zgh");
    strcat(bk1.subject, "just for test");
    bk1.book_id = 100;

    strcpy(bk2.title, "Travelling");
    strcpy(bk2.author, "hcp");
    strcpy(bk2.subject, "go to travel,relax your heart");
    bk2.book_id = 200;

    printBook(&bk1);
    printBook(&bk2);

    return 0;
}

void printBook(struct Books *book)
{
    //对于指针类型的结构体变量来说，访问成员时必须用->，而不能用.了
    //这是需要注意并记住的地方
    printf("the name of book is %s,writen by %s \n", book->title, book->author);
    printf("description:%s \n", book->subject);
    printf("-------------------------\n");
}