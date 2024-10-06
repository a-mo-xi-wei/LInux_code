/*************************************************************************
    > File Name: pthread_create.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年10月06日 星期日 11时04分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
void syserr(char* str){
	perror(str);
	exit(1);
}

struct Student
{
    char* name;
    int age;
    double score;
};


void* func(void* arg){
    int n = 0;
    int num = *(int*)arg;
    char* buff = (char*)arg;
    struct Student s = *(struct Student*)arg;
    while(1){
        printf("分支线程 : %d : %s %d %.2f\n",n++,s.name,s.age,s.score);

        sleep(1);
    }
}
int main(int argc,char* argv[]){
	int n = 0;
    pthread_t pt = 0;
    int ret;
    int m = 888;
    char buff[] = "巴巴爸爸";
    struct Student s = {"weisang", 23 ,99.1239};
    ret = pthread_create(&pt,NULL,func,(void*)&s);
    if(ret!=0) syserr("pthread_create");
    printf("pt : %lu\n",pt);
    while(1){
        printf("主线程 : %d\n",n++);
        sleep(1);
    }
    pthread_join(pt,NULL);  //主线程等待分支线程结束
    printf("主线程结束\n");
    close(0);  //关闭标准输入，防止被分支线程关闭
	return 0;
}
