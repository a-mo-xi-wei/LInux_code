/*************************************************************************
    > File Name: aio_read.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年10月08日 星期二 09时56分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<aio.h>
#include<fcntl.h>
void syserr(char* str){
	perror(str);
	exit(1);
}
#define BUFF_SIZE 1024
int main(int argc,char* argv[]){
	//1. 准备缓冲区
    struct aiocb cb = {0};
    int fd = open("1.txt",O_RDONLY);
    if(fd == -1)syserr("open failed");
    else printf("open succeeded\n");

    cb.aio_fildes = fd;
    //cb.aio_offset = 0;    //偏移量
    cb.aio_buf = malloc(BUFF_SIZE);
    memset((void*)cb.aio_buf, 0, BUFF_SIZE);
    cb.aio_nbytes = BUFF_SIZE - 1;

    //2. 异步读
    int r = aio_read(&cb);
    if(r == -1)syserr("aio_read failed");
    printf("read successful\n");
    //3. 检查是是否操作完毕
    int n = 0;
    while(aio_error(&cb)){
        n++;//轮询
    }

    //4. 得到数据
    r = aio_return(&cb);
    if(r > 0){
        printf("读取到%d字节数据：%s  n : %d\n", r,cb.aio_buf,n);
    }
    //收尾
    free((void*)cb.aio_buf);
    close(fd);
	return 0;
}
