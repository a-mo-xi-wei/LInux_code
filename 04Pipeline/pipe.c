/*************************************************************************
    > File Name: pipe.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月13日 星期五 17时13分07秒
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
//匿名管道
int main(int argc,char* argv[]){
	// 1准备有且只有两个元素的描述符号数组
    int fds[2];             
    //2.把数组变成管道
    pipe(fds);
    //3.创建子进程
    if(fork()){
        //4.使用管道
        char buf[256];
        int n = 0 ;
        int r;
        while(1){
            printf("父进程 读管道:");
            r = read(fds[0],buf,255);
            if(r){
                buf[r] = '\0';
                printf(" %d : %s\n",++n,buf);
                if(strcmp(buf,"123456") == 0)break;
            }
        }
    }
    else{
        //4.使用管道
        char buf[256];
        while(1){
            bzero(buf,256);
            scanf("%s",buf);
            write(fds[1],buf,strlen(buf));
            if(strcmp(buf,"123456") == 0)break;
        }
        printf("子进程结束\n");
    }
    //关闭管道
    printf("关闭管道\n");
    close(fds[0]);
    close(fds[1]);
    printf("父进程结束\n");
	return 0;
}
