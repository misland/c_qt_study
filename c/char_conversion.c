/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Karl Storz
 * @Date: 2020-01-03 16:20:08
 * @LastEditors  : Loki Zhao
 * @LastEditTime : 2020-01-03 16:57:31
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void conversion1();
void conversion2();
void conversion3();

void main()
{
    // conversion1();
    // conversion2();
    conversion3();

    return;
}

//将char *转换为char []
void conversion1()
{
    char *source = "hello world";
    char target[100];
    printf("target : %s,length : %d \n", target, strlen(target));
    strcpy(target, source);
    printf("target : %s,length : %d \n", target, strlen(target));
}

//char[]转换为char *，无须操作，直接赋值即可
void conversion2()
{
    char source[100] = "hello world";
    printf("target : %s,length : %d \n", source, strlen(source));
    char *target = source;
    printf("target : %s,length : %d \n", target, strlen(target));
}

//const char * 转换为char []，也是用strcpy就可以，再转char *就简单了
void conversion3()
{
    //const char *指的是指针指定的是常量，无法通过指针修改所指向的内容，并不是说指针是常量，指针还可以指向其它变量
    const char *source = "hello world";
    printf("source : %s,length : %d \n", source, strlen(source));
    //如下，可以将char *或char []赋值给source
    char *test = "hello world again";
    source = test;
    char target[100];
    strcpy(target, source);
    printf("target : %s,length : %d \n", target, strlen(target));
}