/*************************************************************************
    > File Name: sigqueue.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月28日 星期六 10时48分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/time.h>

void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc,char* argv[]){
    union sigval u;
    u.sival_int = atoi(argv[2]);
    
	int r = sigqueue(atoi(argv[1]),SIGINT,u);
    printf("%d r : %d\n",getpid(),r);
	return 0;
}
