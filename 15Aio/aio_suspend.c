/*************************************************************************
    > File Name: aio_suspend.c
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
#define AIO_LIST_NUM 2
int main(int argc,char* argv[]){
	//1. 准备缓冲区
    struct aiocb cb1 = {0};
    struct aiocb cb2 = {0};

    int fd1 = open("1.txt",O_RDONLY);
    if(fd1 == -1)syserr("open failed");
    else printf("open succeeded\n");

    cb1.aio_fildes = fd1;
    //cb.aio_offset = 0;    //偏移量
    cb1.aio_buf = malloc(BUFF_SIZE);
    memset((void*)cb1.aio_buf, 0, BUFF_SIZE);
    cb1.aio_nbytes = BUFF_SIZE - 1;

    //2. 异步读
    int r = aio_read(&cb1);
    if(r == -1)syserr("aio_read failed");
    printf("aio_read successful\n");
//*********************************** */
    int fd2 = open("2.txt",O_WRONLY | O_APPEND);
    if(fd2 == -1)syserr("open failed");
    else printf("open succeeded\n");

    cb2.aio_fildes = fd2;
    //cb.aio_offset = 0;    //偏移量
    cb2.aio_buf = malloc(BUFF_SIZE);
    memset((void*)cb2.aio_buf, 0, BUFF_SIZE);
    strcpy((char*)cb2.aio_buf,"weiwang\n");
    cb2.aio_nbytes = strlen((char*)cb2.aio_buf);

    //2. 异步写
    r = aio_write(&cb2);
    if(r == -1)syserr("aio_write failed");
    printf("aio_write successful\n");
    //3. 检查是是否操作完毕
    const struct aiocb* aiocb_list[AIO_LIST_NUM] = {0};
    aiocb_list[0] = &cb1;
    aiocb_list[1] = &cb2;
    r = aio_suspend(aiocb_list,AIO_LIST_NUM,NULL);
    if(r == -1)syserr("aio_suspend failed");
    printf("aio_suspend successful finish\n");

    //4. 得到数据
    r = aio_return(&cb1);
    if(r > 0){
        printf("读取到%d字节数据：%s\n", r,(char*)cb1.aio_buf);
    }
    r = aio_return(&cb2);
    if(r > 0){
        printf("读取到%d字节数据：%s\n", r,(char*)cb2.aio_buf);
    }
    //收尾
    free((void*)cb1.aio_buf);
    free((void*)cb2.aio_buf);
    close(fd1);
    close(fd2);
	return 0;
}
