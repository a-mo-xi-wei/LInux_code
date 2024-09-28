/*************************************************************************
    > File Name: sigaction.c//-
    > Author: 威桑//-
    > Mail: 1428206861@qq.com //-
    > Created Time: 2024年09月28日 星期六 10时03分15秒//-
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<signal.h>

void syserr(char* str){
	perror(str);
	exit(1);
}
void hand(int s){
    printf("基本的信号处理函数 : %d\n",s);
}
void handler(int s, siginfo_t *info, void *context){//+
    printf("高级信号处理函数\n");
    printf("s: %d \n",s);
    printf("signal num : %d\n",info->si_signo);
    printf("signal value : %d\n",info->si_value.sival_int);  
    printf("发送信号的进程ID : %d\n",info->si_pid); 
}
int main(int argc,char* argv[]){
    struct sigaction act = {0};
    struct sigaction actOld = {0};
    act.sa_handler = hand;
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT,&act,&actOld);
    int n = 0;
    while(1){
        sleep(1);
        printf("正常运行----%d %d\n",n++,getpid());
    }

	return 0;
}
