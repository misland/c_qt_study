/*
 * @Description: a server app that more reasonable
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-06-03 11:54:06
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-06-03 16:49:31
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

#define IPADDR "127.0.0.1"
#define PORT 8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE 10

typedef struct server_context_st
{
    int cli_cnt;
    int clifds[SIZE];
    fd_set allfds;
    int maxfd;
} server_context_st;
static server_context_st *s_srv_ctx = NULL;

static int create_server_proc(const char *ip, int port)
{
    int fd;
    struct sockaddr_in serveraddr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        fprintf(stderr, "create socket failed,errno:%d,reason:%s \n", errno, strerror(errno));
        return -1;
    }
    int reuse = 1;
    //设置端口释放后立即可以使用，SO_REUSEADDR，如果不设置，端口被释放后，要两分钟才能再次被使用
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        return -1;
    }

    //给结构体赋值ip和端口
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);

    //绑定ip和端口
    if (bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        fprintf(stderr, "bind socket error,errno:%d,reason:%s \n", errno, strerror(errno));
        return -1;
    }
    //绑定完开始监听端口
    listen(fd, LISTENQ);
    return fd;
}

static int accept_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;

    printf("estiblish accept proc \n");
ACCEPT:
    clifd = accept(srvfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
    if (clifd == -1)
    {
        if (errno == EINTR)
        {
            goto ACCEPT;
        }
        else
        {
            fprintf(stderr, "accept failed,errno:%d,reason:%s \n", errno, strerror(errno));
            return -1;
        }
    }
    fprintf(stdout, "accept a new client: %s:%d \n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

    //将新的连接描述符添加到待监听的数组中
    int i = 0;
    for (i = 0; i < SIZE; i++)
    {
        //如果>=0，说明已经有文件描述符了，也就是已经有客户端连接了
        if (s_srv_ctx->clifds[i] < 0)
        {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if (i == SIZE)
    {
        fprintf(stderr, "too many clients \n");
        return -1;
    }
}

static int handle_client_msg(int fd, char *msg)
{
    assert(msg);
    printf("receive client msg:%s \n", msg);
    write(fd, msg, strlen(msg) + 1);
    return 0;
}

static void recv_client_msg(fd_set *readfds)
{
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    for (i = 0; i <= s_srv_ctx->cli_cnt; i++)
    {
        clifd = s_srv_ctx->clifds[i];
        //如果文件描述符小于0，说明没有客户端
        if (clifd < 0)
        {
            continue;
        }
        if (FD_ISSET(clifd, readfds))
        {
            //读取客户端发过来的数据，n表示读到的数据长度
            n = read(clifd, buf, MAXLINE);
            //如果长度<=0，说明没有读到数据
            if (n <= 0)
            {
                fprintf(stdout, "no data,clear fd \n");
                //将结构体中保存的客户端描述符清除掉
                FD_CLR(clifd, &s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clifds[i] = -1;
                continue;
            }
            //读到了数据，处理数据，返回消息给客户端
            handle_client_msg(clifd, buf);
        }
    }
}

static void handle_client_proc(int srvfd)
{
    int clifd = -1;
    int retval = 0;
    //这里把服务端的文件描述符集合赋给了一个临时变量，因为select时会改变参数值，不能直接用服务端的集合
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;
    while (1)
    {
        //每次调用select前，重新设置文件描述符和时间，因为事件发生后，描述符和时间内核将被修改
        FD_ZERO(readfds);
        //将服务端socket描述符重新加入监听集合，客户端的不用添加，因为在上一次的轮询中，应该处理的，都处理过了
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        printf("begin to loop clients,client counts:%d \n", s_srv_ctx->cli_cnt);
        for (i = 0; i < s_srv_ctx->cli_cnt; i++)
        {
            clifd = s_srv_ctx->clifds[i];
            //有客户端就添加到待监听集合中，避免多余轮询
            if (clifd != -1)
            {
                FD_SET(clifd, readfds);
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }

        //开始轮询
        //如果轮询到有描述符变更，会立即返回，如果一直没有描述符变更，到时设置的超时时间也会返回
        retval = select(s_srv_ctx->maxfd + 1, readfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            fprintf(stderr, "select error:errno:%d,reason:%s \n", errno, strerror(errno));
        }
        if (retval == 0)
        {
            // fprintf(stdout, "select time out \n");
        }
        //这里还没有看懂
        if (FD_ISSET(srvfd, readfds))
        {
            accept_client_proc(srvfd);
        }
        else
        {
            fprintf(stdout, "begin to read client messages \n");
            recv_client_msg(readfds);
        }
    }
}

static int server_uninit()
{
    if (s_srv_ctx)
    {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

static int server_init()
{
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL)
    {
        fprintf(stderr, "malloc for server struct error,errno:%d,reason:%s \n", errno, strerror(errno));
        return -1;
    }

    memset(s_srv_ctx, 0, sizeof(server_context_st));
    int i = 0;
    for (; i < SIZE; i++)
    {
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}

int main()
{
    int srvfd;
    if (server_init() < 0)
    {
        fprintf(stderr, "server init failed \n");
        return -1;
    }

    srvfd = create_server_proc(IPADDR, PORT);
    if (srvfd < 0)
    {
        fprintf(stderr, "create socket error \n");
        goto err;
    }
    fprintf(stdout, "crate socket successfully,fd:%d \n", srvfd);
    handle_client_proc(srvfd);
    server_uninit();
    return 0;
err:
    server_uninit();
    return -1;
}