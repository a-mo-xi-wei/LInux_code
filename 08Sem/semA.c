#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    printf("Thread %d is waiting to enter the critical section.\n", thread_id);
    sem_wait(&semaphore);  // 等待信号量

    printf("Thread %d has entered the critical section.\n", thread_id);
    // 模拟对共享资源的访问
    sleep(1);

    printf("Thread %d is leaving the critical section.\n", thread_id);
    sem_post(&semaphore);  // 释放信号量
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // 初始化信号量
    sem_init(&semaphore, 0, 1);

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // 等待所有线程结束
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&semaphore);
    return 0;
}
