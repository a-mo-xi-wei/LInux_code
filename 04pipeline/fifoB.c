 /*************************************************************************
    > File Name: fifoA.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月14日 星期六 22时46分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc,char* argv[]){
    //2.打开
    int fd = open(argv[1],O_WRONLY);
    if(fd == -1){
        //删除管道文件
        unlink(argv[1]);
        syserr("open failed ...\n");
    }
    printf("open fifo successed\n");
    //3.读
    char buf[256];
    int n = 0;
    while(1){
        printf("你要发送 : ");
        scanf("%s", buf);
        n = write(fd,buf,strlen(buf));
        printf("发送 %d 字节数据!\n",n);
    }
    //5.关闭
    close(fd);
    //6.删除管道文件
    unlink(argv[1]);
	return 0;
}
