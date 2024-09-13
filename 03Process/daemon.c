#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc ,char* argv[]) {
    //1.重设当前文件权限
    umask(0);
    //2. 创建子进程
    int ret = fork();
    if(ret < 0){printf("Failed to fork\n"); exit(0);}
    //3. 让父进程结束
    if(ret > 0) {printf("父进程结束!\n"); exit(0);}
    if(ret == 0) {
        printf("pid : %d\n",getpid());
        //4. 子进程创建新会话
        setsid();
        //5. 忽略SIGCHLD SIGHUP信号
        signal(SIGCHLD, SIG_IGN);
        signal(SIGHUP, SIG_IGN);
        //6. 改变工作目录
        chdir("/");
        //7. 重定向文件描述符
        int fd = open("dev/null",O_RDWR);
        dup2(fd,0);
        dup2(fd,1);
    }
    while(1) {//模拟守护进程工作
        sleep(1);
    }


    return 0;
}