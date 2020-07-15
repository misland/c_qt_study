/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-30 21:36:19
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-05-30 22:21:28
 */
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    //每一个bit可以监控一个fd，总共可监控的总数就是sezeof(fd_set)*8
    printf("size of fd_set:%ld \n", sizeof(fd_set));
    printf("size of FD_SETSIZE:%d \n", FD_SETSIZE);
    fd_set rset;

    struct timeval tv;
    int err;

    FD_ZERO(&rset);
    //把0加入集合，这里0表示标准输入吗？
    FD_SET(0, &rset);

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    err = select(1, &rset, NULL, NULL, &tv);

    if (err == 0)
    {
        printf("select time out \n");
    }
    else if (err == -1)
    {
        printf("fail to select \n");
    }
    else
    {
        printf("data is avaliable \n");
    }

    return 0;
}