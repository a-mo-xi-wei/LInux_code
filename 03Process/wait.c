#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc ,char* argv[]) {
    printf("当前进程ID : %d\n",getpid());
    sleep(3);
    int n = 4;
    int pid = fork();
    if(pid) {       //父进程返回子进程的ID
        for(int i=0;i<3;i++) {
            printf("我是父进程 :%d %d %d \n",n+=1,getpid(),getppid());
            sleep(1);
        }
        printf("父进程活干完了，等待子进程结束\n");
        int sts = 666;
        pid_t r = wait(&sts);
        printf("父进程结束 : %d %d \n",r,sts);
    }else {         //子进程的fork返回0
        for(int i=0;i<5;i++) {
            printf("-------我是子进程:%d %d %d\n",n+=3,getpid(),getppid());
            sleep(1);
        }
    }

    return 0;
}