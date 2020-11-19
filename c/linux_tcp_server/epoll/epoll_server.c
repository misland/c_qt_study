/*
 * @Description: copy from https://www.cnblogs.com/Anker/archive/2013/08/17/3263780.html
 * @Author: Loki Zhao
 * @Copyright: Loki Zhao
 * @Date: 2020-07-15 10:54:16
 * @LastEditors: Loki Zhao
 * @LastEditTime: 2020-07-15 16:39:02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 3111
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

//建立socket并绑定
static int socket_bind(const char *ip, int port);
//多路复用
static void do_epoll(int listenfd);
//处理事件
static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf);
//处理收到的客户端连接
static void handle_accept(int epollfd, int listenfd);
//读取客户端发送过来的数据
static void do_read(int epollfd, int fd, char *buf);
//将回馈信息发送给客户端
static void do_write(int epollfd, int fd, char *buf);
//添加事件
static void add_event(int epollfd, int fd, int state);
//修改事件
static void modify_event(int epollfd, int fd, int state);
//删除事件
static void delete_event(int epollfd, int fd, int state);

int main(int argc, char *argv[])
{
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}

static int socket_bind(const char *ip, int port)
{
    int listenfd;
    struct sockaddr_in servaddr;
    //建立socket，返回fd
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    //错误处理
    if (listenfd == -1)
    {
        printf("create socket failed \n");
        exit(1);
    }

    int reuse = 1;
    //设置端口释放后立即可以使用，SO_REUSEADDR，如果不设置，端口被释放后，要两分钟才能再次被使用
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        printf("set SO_REUSEADDR failed \n");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    //绑定socket的fd
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("bind socket error \n");
        exit(2);
    }
    return listenfd;
}

static void do_epoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);
    //创建epoll，返回fd
    epollfd = epoll_create(FDSIZE);
    printf("epoll fd:%d\n", epollfd);
    //添加监听事件fd
    add_event(epollfd, listenfd, EPOLLIN);
    for (;;)
    {
        //ret是事件完成需要处理的数量，单客户端时永远是1，多客户端时就不同了
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        printf("ret:%d\n", ret);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
    close(epollfd);
}

static void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
    int i;
    int fd;
    for (i = 0; i < num; i++)
    {
        fd = events[i].data.fd;
        //EPOLLIN表示，有连接到达，需要接收数据
        if ((fd == listenfd) && (events[i].events & EPOLLIN))
        {
            handle_accept(epollfd, listenfd);
        }
        else if (events[i].events & EPOLLIN)
        {
            do_read(epollfd, fd, buf);
        }
        //EPOLLOUT表示有数据要写，即发回客户端
        else if (events[i].events & EPOLLOUT)
        {
            //收到什么数据，就返回什么数据
            //在并发时，buf值可能是其它client的发过来的内容，就会出错了
            //所以，这个示例只能处理单客户端或低并发情况
            do_write(epollfd, fd, buf);
        }
    }
}

static void handle_accept(int epollfd, int listenfd)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
    if (clifd == -1)
    {
        printf("accept client request failed\n");
    }
    else
    {
        printf("accept a new client:%d,ip:%s,port:%d \n", clifd, inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
}

static void do_read(int epollfd, int fd, char *buf)
{
    int nread;
    nread = read(fd, buf, MAXSIZE);
    if (nread == -1)
    {
        printf("read client message failed\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else if (nread == 0)
    {
        printf("client closed\n");
        close(fd);
        printf("delete event for client:%d \n", fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else
    {
        printf("client message:%s\n", buf);
        modify_event(epollfd, fd, EPOLLOUT);
    }
}

static void do_write(int epollfd, int fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1)
    {
        printf("write feedback message failed\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else
    {
        printf("send message back to client:%d completely,notify watcher \n", fd);
        modify_event(epollfd, fd, EPOLLIN);
    }
    memset(buf, 0, MAXSIZE);
}

static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}