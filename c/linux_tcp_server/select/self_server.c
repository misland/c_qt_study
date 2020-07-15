/*
 * @Description: copy from https://www.cnblogs.com/Anker/archive/2013/08/14/3258674.html
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-30 22:07:22
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-15 16:43:08
 */
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdlib.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, testfds;
    //建立服务器端socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //server参数，ip、port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);
    server_len = sizeof(server_address);

    //绑定socket，开始监听
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while (1)
    {
        char ch;
        int fd;
        int nread;
        //将需要监控的描述符集合copy到select查询队列中，select会对其修改，所以一定要分开使用变量，这里用的赋值，而不是直接引用指针
        testfds = readfds;
        printf("server waiting \n");

        //FD_SETSIZE是个宏，表示系统默认的最大文件描述符
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        if (result < 1)
        {
            perror("server5 \n");
            exit(1);
        }

        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            //判断描述符是否有被置位的，即是否有需要处理的
            if (FD_ISSET(fd, &testfds))
            {
                //判断需要处理的是不是服务器socket监听，如果是，说明有新的client连接进来
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds);
                    printf("add client on fd:%d \n", client_sockfd);
                }
                else
                {
                    //读取数据，赋给nrad
                    ioctl(fd, FIONREAD, &nread);
                    printf("nread:%d \n", nread);
                    //如果数据请求完毕，关闭套接字，从集合中清除描述符
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("removing client on fd:%d \n", fd);
                    }
                    //处理客户数据
                    else
                    {
                        read(fd, &ch, 1);
                        printf("read content from client:%d, data is:%c \n", fd, ch);
                        sleep(5);
                        ch++;
                        printf("send data back to client on fd:%d,data is:%c \n", fd, ch);
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }

    return 0;
}