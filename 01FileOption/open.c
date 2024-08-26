/*
	创建命令行参数输入名字的文件
	存储用户输入的学生姓名年龄和成绩
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
}stu={"张飞",18,88.88};
int main(int argc,char* argv[]){
	if(argc < 2){
		printf("请命令行输入文件名!\n");
		exit(-1);//结束当前进程
	}

	int fd;
	fd = open(argv[1],O_WRONLY);
	if(-1 == fd){
		printf("打开%s失败:%m\n",argv[1]);
		printf("尝试创建文件!\n");
		fd = open(argv[1],O_WRONLY|O_CREAT,0666);
		if(-1 == fd){
			printf("创建%s都失败了 失败原因:%m,俺们不玩了\n",argv[1]);
			exit(-1);
		}
		printf("创建文件成功!\n");
	}
	printf("打开文件成功!\n");

#if 0
	write(fd,(const char*)&stu,sizeof(stu));
#else
	write(fd,stu.name,sizeof(stu.name));
	write(fd,(const char*)&(stu.age),sizeof(stu.age));
	write(fd,(const char*)&(stu.score),sizeof(stu.score));
#endif

	//sleep(20);
	printf("over!\n");
	close(fd);
}
