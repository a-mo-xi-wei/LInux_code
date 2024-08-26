/*************************************************************************
    > File Name: mkdir.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年08月26日 星期一 18时58分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc ,char* argv[]){
	if(argc < 2){
        printf("请输入要创建的目录名！\n");
        exit(-1);
    }
    else{
        printf("创建%d个目录\n",argc-1);
        for (size_t i = 1; i < argc; i++){
            mkdir(argv[i],0777);
        }
    }
    printf("创建完毕\n");
    system("ls");
	return 0;
}
