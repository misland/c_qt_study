#include <stdio.h>

// 在宏定义中，符号\是延续标记存在，表示未结束，下一行继续
//a和b也相当于宏了，可以用#a和#b来表示
#define test(a, b) \
    printf(#a " and " #b ", welcome to oure country\n")

//两个#可以将两个参数连起来，有点类似于js中的eval
//如果n=1，token##n在执行时表示用token1这个参数
#define hello(n) \
    printf("token" #n " is %d\n", token##n);

#ifndef MESSAGE
#define MESSAGE  "HELLO"
#endif

int main()
{
    //传字符串不需要加双引号了，需要注意，传什么，宏中就原样使用
    test(Mike, Jason);

    int token30 = 100;
    //执行时实际使用token30这个变量
    hello(30);

    printf("MESSAGE is:%s\n", MESSAGE);

    return 0;
}