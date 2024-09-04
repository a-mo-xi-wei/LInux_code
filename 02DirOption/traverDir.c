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
//#include<features.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
char err[256];
void syserr(char* str){
    sprintf(err,"opendir %s 失败 \n",str);
	perror(err);
	exit(1);
}
void removeTrailingSlash(char* path) {
    size_t length = strlen(path);  // 获取字符串长度

    // 检查最后一个字符是否是 '/'，并确保字符串非空
    if (length > 0 && path[length - 1] == '/') {
        path[length - 1] = '\0';  // 将最后一个字符设置为字符串结束符 '\0'
    }
}
void traverse(char* path){
    char fileName[128];

    removeTrailingSlash(path);    
    DIR* pDir = opendir(path);
    if(pDir == NULL)syserr(path);
    printf("打开目录成功\n");

    int num = 0;
    struct dirent* pEntry = NULL;
    while(1){
        pEntry = readdir(pDir);
        if(pEntry == NULL)break;
        if(pEntry->d_name[0] == '.' || strcmp(pEntry->d_name,"..") == 0) continue;
        //printf("path : %s\n",path);
        //printf("d_name : %s\n",pEntry->d_name);
        sprintf(fileName,"%s/%s",path,pEntry->d_name);
        //printf("fileName : %s\n",fileName);
        if(pEntry->d_type == DT_DIR){
            printf("目录 : %d : %s\n",num + 1 ,fileName);
            traverse(fileName);
        }else{
            printf("文件 : %d : %s\n",num + 1 ,fileName);
        }
        num++;
    }
    printf("遍历完毕\n");
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
