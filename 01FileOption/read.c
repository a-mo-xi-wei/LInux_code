/*
	创建命令行参数输入名字的文件
	读文件
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
struct Student{
	char name[20];
	int age;
	double score;
};
int main(int argc,char* argv[]){
	if(argc < 2){
		printf("请命令行输入文件名!\n");
		exit(-1);//结束当前进程
	}

	int fd = open(argv[1],O_RDONLY);
	if(-1 == fd) 
		printf("打开%s失败:%m\n",argv[1]),exit(-1);
	printf("打开文件成功!\n");
	struct Student s = {0};
#if 0
	read(fd,&s,sizeof s);
	printf("%s - %d - %g\n",s.name,s.age,s.score);
#else
	read(fd,s.name,20);
	//lseek(fd,4,SEEK_CUR);//当前位置往后偏移4字节
	read(fd,&s.age,sizeof(int));
	read(fd,&s.score,sizeof(double));
	printf("%s - %d - %g\n",s.name,s.age,s.score);
#endif
	close(fd);
}
