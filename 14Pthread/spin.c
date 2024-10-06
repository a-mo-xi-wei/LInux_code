/*************************************************************************
    > File Name: spin.c
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
pthread_spinlock_t spin;
//_Atomic int n = 0;
int n = 0;
void *func()
{
    for (int i = 0; i < 5000000; i++)
    {
        pthread_spin_lock(&spin);
        n++;
        pthread_spin_unlock(&spin);
    }
}
void* f1()
{
    while(1)
    {
        pthread_spin_lock(&spin);
        printf("线程一-------------\n");
        sleep(1);
        pthread_spin_unlock(&spin);
    }
}
void* f2()
{
    while(1)
    {
        pthread_spin_lock(&spin);
        printf("线程二-------------\n");
        sleep(1);
        pthread_spin_unlock(&spin);
    }
}
int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    //初始化互斥量
    pthread_spin_init(&spin, 0);
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("n = %d\n", n); // 100
    //销毁互斥量
    pthread_spin_destroy(&spin);
    return 0;
}
