/*************************************************************************
    > File Name: aio_write.c
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
    int fd = open("2.txt",O_WRONLY | O_APPEND);
    if(fd == -1)syserr("open failed");
    else printf("open succeeded\n");

    cb.aio_fildes = fd;
    //cb.aio_offset = 0;    //偏移量
    cb.aio_buf = malloc(BUFF_SIZE);
    memset((void*)cb.aio_buf, 0, BUFF_SIZE);

    strcpy(cb.aio_buf,"weiwang\n");

    cb.aio_nbytes = strlen(cb.aio_buf);

    //2. 异步写
    int r = aio_write(&cb);
    if(r == -1)syserr("aio_write failed");
    printf("write successful\n");
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
