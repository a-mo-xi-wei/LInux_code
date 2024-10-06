/*************************************************************************
    > File Name: thread.c
    > Author: 威桑
    > Mail: 1428206861@qq.com
    > Created Time: 2024年10月06日 星期日 15时52分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>

void syserr(char *str)
{
    perror(str);
    exit(1);
}
void hand(int s)
{
    if (s == 2)
    {
        printf("收到信号QAQ\n");
        pthread_exit((void *)666);
    }
}
void *f(void *a)
{
    signal(2, hand);
    for (int i = 0; i < 5; i++)
    {
        printf("线程1-----: %d\n", i);
        sleep(1);
    }
    return NULL;
}

void *f1(void *a)
{
    for (int i = 0; i < 8; i++)
    {
        printf("线程2-----: %d\n", i);
        sleep(1);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, f, NULL);
    pthread_create(&t2, NULL, f1, NULL);
    int n = 0;
    while (1)
    {
        if (++n > 9)
            break;
        if (n == 3)
            pthread_kill(t1, 2);
        // if(++n==3)pthread_cancel(t2);
        printf("主线程\n");
        sleep(1);
    }
    void *p1;
    void *p2;
    pthread_join(t1, &p1);
    pthread_join(t2, &p2);
    printf("ret1 = %d ret2 = %d\n", p1, p1);
    return 0;
}
/*在多线程程序中，如果某个线程（例如 t1）注册了信号处理函数，那么即使 t1 线程已经退出，
整个进程依然保持对信号的响应。当进程接收到 SIGINT 信号时，主线程可能并没有处理该信号的处理程序，
因此默认行为是仍然触发其他已经注册过的信号处理程序。*/