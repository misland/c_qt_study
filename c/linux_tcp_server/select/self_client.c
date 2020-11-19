/*
 * @Description: 
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-05-30 22:35:57
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-15 16:37:07
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main()
{
    char res[4096] = {0};
    int client_sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char cmd[] = "require blueriver_api 2.18.0.0\n";
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("localhost");
    address.sin_port = htons(6970);
    len = sizeof(address);
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("connect server failed \n");
        exit(1);
    }
    //第一次读写
    printf("the first time send data to server \n");
    int nwrite = write(client_sockfd, &cmd, strlen(cmd));
    printf("length write to server:%d\n", nwrite);
    int nread = read(client_sockfd, &res, 1024);
    if (nread > 0)
    {
        printf("response from server is: %s \n", res);
    }
    else
    {
        printf("receive server message failed\n");
    }

    close(client_sockfd);

    return 0;
}