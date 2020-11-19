/*
 * @Description: monitor for blueriver
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
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int indexOf(char *str1, char *str2);

int create_socket(char *ip, int port);

int load_layout(int sockfd, FILE *layout);

int main(int argc, char *argv[])
{
    //读取layout配置文件
    FILE *layout;
    if (argc != 2)
    {
        printf("please specify the layout file\n");
        exit(1);
    }

    layout = fopen(argv[1], "r");
    if (layout == NULL)
    {
        printf("open layout file failed\n");
        exit(2);
    }

    while (1)
    {
        //创建socket，发送cmd指令，加载layout
        char res[1024] = {0};
        int client_sockfd;
        client_sockfd = create_socket("localhost", 6970);
        if (client_sockfd == -1)
        {
            exit(3);
        }

        //导入多画面模块，执行相关命令
        char cmd[] = "require multiview 1.1.0\n";
        int nwrite = write(client_sockfd, &cmd, strlen(cmd));
        int tem = read(client_sockfd, &res, 1024);

        //检查当前已加载的布局
        strcpy(cmd, "list layout\n");
        write(client_sockfd, &cmd, strlen(cmd));
        tem = read(client_sockfd, &res, 1024);
        bool loaded = false;
        if (tem > 0)
        {
            printf("response:%s,index:%d\n", res, indexOf(res, "pip_1080"));
            if (indexOf(res, "pip_1080") > 0)
            {
                printf("layout has been loaded\n");
                loaded = true;
            }
        }
        else
        {
            printf("receive server message failed\n");
            exit(3);
        }

        //若布局已加载，不再重复加载
        if (!loaded)
        {
            load_layout(client_sockfd, layout);
            printf("\nlayout loaded\n");
        }

        close(client_sockfd);
        printf("hello\n");

        //等待下一次轮询
        sleep(5);
    }
    fclose(layout);

    return 0;
}

int load_layout(int sockfd, FILE *layout)
{
    char *line = NULL;
    char res[1024] = {0};
    size_t line_len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &line_len, layout)) != EOF)
    {
        char tem[line_len];
        strncpy(tem, line, line_len - 2);
        int nwrite = write(sockfd, &tem, strlen(tem));
        int rread = read(sockfd, &res, 1024);
        if (rread > 0)
        {
            printf("server response:%s\n", res);
        }
    }
    free(line);
    return 0;
}

int create_socket(char *ip, int port)
{
    int client_sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    len = sizeof(address);
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        printf("connect server failed\n");
        return -1;
    }
    return client_sockfd;
}

int indexOf(char *str1, char *str2)
{
    char *p = str1;
    int i = 0;
    p = strstr(str1, str2);
    if (p == NULL)
        return -1;
    else
    {
        while (str1 != p)
        {
            str1++;
            i++;
        }
    }
    return i;
}