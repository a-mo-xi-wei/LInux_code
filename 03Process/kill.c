#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>

int main(int argc,char* argv[]) {
    int pid = atoi(argv[1]);
    kill(pid,9);
    printf("给%d进程发送信号9完毕\n",pid);

    return 0;
}