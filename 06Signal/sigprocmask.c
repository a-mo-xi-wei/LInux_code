/*************************************************************************
    > File Name: sigprocmask.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月28日 星期六 17时46分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/time.h>

void syserr(char* str){
	perror(str);
	exit(1);
}
void hand(int n){
    printf("信号处理函数\n");

}
int main(int argc,char* argv[]){
    printf("pid : %d\n",getpid());
    sigset_t set,oldSet;
    sigemptyset(&set);
    sigaddset(&set,2);
    signal(2,hand);
    sleep(10);
    int r;
    if(sigismember(&set,2) == 1){
        printf("设置屏蔽\n");
        r = sigprocmask(SIG_BLOCK,&set,&oldSet);
        if(r == -1)printf("设置屏蔽失败:%m\n");
        else printf("设置屏蔽成功\n");
    }
    sleep(10);
    if(sigismember(&set,2) == 1){
        printf("解除屏蔽\n");
        r = sigprocmask(SIG_UNBLOCK,&set,&oldSet);
        if(r == -1)printf("解除屏蔽失败:%m\n");
        else printf("解除屏蔽成功\n");
    }
    int n = 0;
    while(1){
        sleep(1);
        printf("正常运行-----%d %d\n",n++,getpid());

    }

	return 0;
}
