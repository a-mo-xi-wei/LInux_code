/*************************************************************************
    > File Name: rwlock.c
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
// 创建读写锁
pthread_rwlock_t rwlock;
int n = 0;
void *func()
{
    for (int i = 0; i < 5000000; i++)
    {
        pthread_rwlock_wrlock(&rwlock);
        n++; // 临界数据
        pthread_rwlock_unlock(&rwlock);
    }
}

void* f1()
{
    while(1)
    {
        //加读锁
        //pthread_rwlock_rdlock(&rwlock);
        //加读锁
        pthread_rwlock_wrlock(&rwlock);
        printf("线程一-------------\n");
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
    }
}
void* f2()
{
    while(1)
    {
         //加读锁
        //pthread_rwlock_rdlock(&rwlock);
        //加读锁
        pthread_rwlock_wrlock(&rwlock);
        printf("线程二-------------\n");
        sleep(1);
        pthread_rwlock_unlock(&rwlock);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);
#if 0
    pthread_create(&t1, NULL, func, NULL);
    pthread_create(&t2, NULL, func, NULL);
#else 
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);
#endif

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("n = %d\n", n); // 100
    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
