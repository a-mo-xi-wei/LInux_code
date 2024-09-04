/*************************************************************************
    > File Name: write.c
    > Author: 威桑
    > Mail: 1428206861@qq.com
    > Created Time: 2024年09月04日 星期三 15时58分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>

#define NUM 10000
void syserr(char *str)
{
    perror(str);
    exit(1);
}
typedef struct Student
{
    char name[20];
    int age;
    double score;
} Student;
int main(int argc, char *argv[])
{
    Student student = {"威桑", 18, 99.9};
    int fd = open("stu.data", O_RDWR);
    if (-1 == fd)
    {
        printf("打开%s失败:%m\n", "stu.data");
        printf("尝试创建文件!\n");
        fd = open("stu.data", O_RDWR | O_CREAT, 0666);
        if (-1 == fd)
        {
            printf("创建%s都失败了 失败原因:%m,不玩了\n", "stu.data");
            exit(-1);
        }
        printf("创建文件成功!\n");
    }
    printf("打开文件成功!\n");

    int r = ftruncate(fd, NUM * sizeof(student));
    if (r == -1)
    {
        close(fd);
        syserr("ftruncate error \n");
    }
    printf("调整文件大小成功\n");
    // 文件映射成虚拟内存
    Student *p = mmap(NULL,
                      NUM * sizeof(student),
                      PROT_WRITE | PROT_READ,
                      MAP_SHARED,
                      fd, 0);
    if (p == MAP_FAILED)
    {
        close(fd);
        syserr("mmap error \n");
    }
    printf("文件映射成功!\n");

    struct timeval oldtime, newtime;
    gettimeofday(&oldtime, NULL);

    // 内存操作
    Student *tmp = p;
    for (size_t i = 0; i < NUM; i++)
    {
        memcpy(tmp, &student, sizeof(student));
        tmp++;
    }

    gettimeofday(&newtime, NULL);
    printf("%ld %ld\n", newtime.tv_sec - oldtime.tv_sec, newtime.tv_usec - oldtime.tv_usec);
    // 解除映射
    munmap(p, NUM * sizeof(student));
    close(fd);

    return 0;
}
