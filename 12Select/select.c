/*************************************************************************
    > File Name: select.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年10月02日 星期三 09时05分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/select.h>
void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc,char* argv[]){
	fd_set fds;
    fd_set fdsOut;

    

    FD_ZERO(&fdsOut);
    FD_SET(1, &fdsOut);

    int r ;
    char buf[1024];

    while(1){
        FD_ZERO(&fds);
        FD_SET(0, &fds);

        r = select(2,&fds,&fdsOut,NULL,NULL); //阻塞
        if(r > 0){
            if(FD_ISSET(0,&fds)){
                printf("是0有动静\n");
                printf("处理\n");
                scanf("%s",buf);
                //清空
                // FD_CLR(0,&fds);
            }else if FD_ISSET(1,&fdsOut){
                printf("输出有动静------\n");
                FD_CLR(1,&fdsOut);
                FD_ZERO(&fdsOut);
            }
        }
        else if(r == 0){
            printf("没有动静\n");
        }else{
            printf("错误 : %m\n");
        }

    }
	return 0;
}
