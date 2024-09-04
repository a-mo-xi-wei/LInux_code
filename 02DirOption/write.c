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
    int fd = open("stu.data", O_WRONLY);
    if (-1 == fd)
    {
        printf("打开%s失败:%m\n", "stu.data");
        printf("尝试创建文件!\n");
        fd = open("stu.data", O_WRONLY | O_CREAT, 0666);
        if (-1 == fd)
        {
            printf("创建%s都失败了 失败原因:%m,不玩了\n", "stu.data");
            exit(-1);
        }
        printf("创建文件成功!\n");
    }
    printf("打开文件成功!\n");

    struct timeval oldtime, newtime;
    gettimeofday(&oldtime, NULL);
    for (size_t i = 0; i < NUM; i++)
    {
        write(fd, (const char *)&student, sizeof(student));
    }
    gettimeofday(&newtime, NULL);
    printf("%ld %ld\n", newtime.tv_sec - oldtime.tv_sec, newtime.tv_usec - oldtime.tv_usec);
    return 0;
}
