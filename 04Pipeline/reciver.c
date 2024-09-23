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
	//1. 创建管道文件
    int ret = mkfifo(argv[1],0666);
    if(ret == -1)syserr("mkfifo failed");
    printf("创建管道文件%s成功\n",argv[1]);
    //2.打开
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1){
        //删除管道文件
        unlink(argv[1]);
        syserr("open failed ...\n");
    }
    printf("open fifo successed\n");
    //3.读
    char filename[256] = {0};
    //3.1 接受文件名
    int r = read(fd,filename,255);
    if(r > 0){
        printf("接受文件名成功 ： %s\n",filename);
    }

    int dstFd = open(filename,O_WRONLY | O_CREAT,0666);
    if(dstFd == -1){
        printf("创建文件失败%m\n");
    }

    //3.2接受文件大小
    int filesize = 0;
    r = read(fd,&filesize,sizeof(int));
    if(r == 4){
        printf("文件大小为 ： %d\n",filesize);
    }

    char temp[1024];
    int cnt = 0;
    while(1){
        r = read(fd, temp, 1024);
        if(r){
            cnt += r;
            write(dstFd, temp, r);
            if(cnt >= filesize)break;//接受完毕，结束循环
        }
    }

    close(dstFd);

    //5.关闭
    close(fd);
    //6.删除管道文件
    unlink(argv[1]);
	return 0;
}
