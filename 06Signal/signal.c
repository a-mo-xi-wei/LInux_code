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
#include<sys/types.h>
#include<sys/time.h>

void syserr(char* str){
	perror(str);
	exit(1);
}
void handler(int signum){
    switch(signum){
        case SIGALRM:
            printf("收到定时器信号:%d\n",signum);
            break;
    }
}
int main(int argc,char* argv[]){
	signal(SIGALRM,handler);
    struct itimerval tv = {0};
    tv.it_value.tv_sec = 2;
    setitimer(ITIMER_REAL,&tv,NULL);
    int n =0 ;
    while(1){
        printf("正常运----%d %d\n",n++,getpid());
        sleep(1);
        if(n%3==0)raise(SIGALRM);
    }

    return 0;
}

    