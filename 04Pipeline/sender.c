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
    //3.写
    char filename[256];
    int r;
    int n = 0;
    printf("请输入要发送的文件名：\n");
    scanf("%s",filename);
    write(fd,filename,strlen(filename));

    int srcFd = open(filename,O_RDONLY);
    if(srcFd == 01){
        printf("打开文件失败 %m\n");
        close(fd);
        unlink(argv[1]);
        return -1;
    }
    printf("打开文件%s成功!\n",filename);

    //获取文件大小并发送文件大小
    struct stat fs = {0};
    stat(filename,&fs);
    write(fd,&(fs.st_size),sizeof(fs.st_size));

    char temp[1024];
    while(1){
        r = read(srcFd,temp,1024);        
        if(r > 0){
            write(fd,temp,r);   //读到多少发送多少
        }
        else{
            break;
        }
    }

    //4.关闭
    close(srcFd);
    close(fd);
    //6\5.删除管道文件
    unlink(argv[1]);
	return 0;
}
