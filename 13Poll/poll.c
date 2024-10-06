/*************************************************************************
    > File Name: poll.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年10月02日 星期三 15时57分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<poll.h>
#include<fcntl.h>
void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc,char* argv[]){
	//1. 创建结构体数组
    struct pollfd fds[200];

    //2. 填充结构体数组 设置要监视的描述符号
    fds[0].fd = 0; // stdin
    fds[0].events = POLLIN;
    char buff[1024];
    //3. 开始轮询
    while(1){
        int ret = poll(fds,1,0);  // -1表示阻塞
        if(ret == -1){
            syserr("poll error");
        }
        else if(ret == 0){
            continue;
        }
        else{
            if(fds->events & POLLIN){   //自身原本是阻塞的
                memset(buff,0,sizeof(buff));
                scanf("%s",buff);
                printf(">>%s\n",buff);
            }
        }
    }
	return 0;
}
