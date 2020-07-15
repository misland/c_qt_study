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
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main()
{
    int client_sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'S';
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8787);
    len = sizeof(address);
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("connect server failed \n");
        exit(1);
    }
    //第一次读写
    printf("the first time send data to server \n");
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &ch, 1);
    printf("the first time:char from server is: %c \n", ch);
    // sleep(5);

    //第二次读写
    // printf("the second time send data to server \n");
    // write(client_sockfd, &ch, 1);
    // read(client_sockfd, &ch, 1);
    // printf("the second time:char from server is: %c \n", ch);

    close(client_sockfd);

    return 0;
}