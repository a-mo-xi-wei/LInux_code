/*************************************************************************
    > File Name: cond.c
    > Author: 威桑
    > Mail: 1428206861@qq.com
    > Created Time: 2024年10月06日 星期日 18时43分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
void syserr(char *str)
{
    perror(str);
    exit(1);
}
// 创建条件变量
pthread_mutex_t mutex; // 互相排斥，其他线程解锁前无法加锁，可能很久抢占不到加锁权
pthread_cond_t cond;

//_Atomic int n = 0;
int n = 0;
void *func()
{
    for (int i = 0; i < 5000000; i++)
    {
        pthread_mutex_lock(&mutex);
        n++; // 临界数据
        pthread_mutex_unlock(&mutex);
    }
}

void f1()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);//阻塞式等待 等待信号
        printf("线程一-------------\n");
        pthread_mutex_unlock(&mutex);
    }
}
void f2()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        printf("线程二-------------\n");
        pthread_mutex_unlock(&mutex);
    }
}
void f3()
{
    while (1)
    {
        pthread_cond_signal(&cond);//向某个线程发送信号
        //pthread_cond_broadcast(&cond);//向所有线程发送信号
        sleep(1);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3;
    // 初始化条件变量
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);
    pthread_create(&t3, NULL, f3, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    printf("n = %d\n", n); // 100
    // 销毁条件变量
    pthread_mutex_destroy(&mutex);
    return 0;
}
