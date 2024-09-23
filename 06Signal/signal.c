/*************************************************************************
    > File Name: signal.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月23日 星期一 19时15分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<signal.h>

void syserr(char* str){
	perror(str);
	exit(1);
}
void handler(int signum){
    printf("接收到信号%d\n",signum);
}
int main(int argc,char* argv[]){
	signal(2,handler);
    int n = 0;
    while(1){
        printf("n:%d\n",n++);
        sleep(1);
    }
	return 0;
}
