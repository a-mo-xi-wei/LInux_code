/*************************************************************************
    > File Name: traverDir.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年08月26日 星期一 19时10分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
char err[256];
void syserr(char* str){
    sprintf(err,"opendir %s 失败 \n",str);
	perror(err);
	exit(1);
}

void traverse(const char* path){
    DIR* pDir = opendir(path);
    if(pDir == NULL)syserr(path);
    printf("打开目录成功\n");
    int num = 0;
    while(1){
        struct dirent* pEntry = readdir(pDir);
        if(pEntry == NULL)break;
        if(strcmp(pEntry->d_name,".") == 0 || strcmp(pEntry->d_name,"..") == 0) continue;
        printf("这是 %s 里第 %d 个文件 ：%s\n",path, ++num , pEntry->d_name);

    }
    closedir(pDir);
}

int main(int argc,char* argv[]){
	if(argc < 2){
        printf("请输入要创建的目录名！\n");
        exit(-1);
    }
    traverse(argv[1]);
    printf("遍历完成\n");
    
    return 0;
}
