/*************************************************************************
    > File Name: mutex.c
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
pthread_mutex_t mutex;//互相排斥，其他线程解锁前无法加锁，可能很久抢占不到加锁权
//_Atomic int n = 0;
int n = 0;
void *func()
{
    for (int i = 0; i < 5000000; i++)
    {
        pthread_mutex_lock(&mutex);
        n++;//临界数据
        pthread_mutex_unlock(&mutex);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    //初始化互斥量
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, func, NULL);
    pthread_create(&t2, NULL, func, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("n = %d\n", n); // 100
    //销毁互斥量
    pthread_mutex_destroy(&mutex);
    return 0;
}
