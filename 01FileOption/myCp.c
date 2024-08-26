#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
int main(int argc,char* argv[]){
	if(argc < 3){
		printf("请输入文件名和拷贝后文件名!\n");
		exit(-1);//结束当前进程
	}

	//拷贝argv[1] 为 argv[2]

	int fdSrc = open(argv[1],O_RDONLY);
	if(-1 == fdSrc) printf("打开待拷贝文件失败:%m\n"),exit(-1);
	printf("打开待拷贝文件%m\n");

	int fdDst = open(argv[2],O_WRONLY|O_CREAT,0666);
	if(-1 == fdDst) printf("创建拷贝后文件失败:%m\n"),exit(-1);
	printf("创建拷贝后文件%m\n");

	int r;
	char temp[1024];
	while(1){
		r = read(fdSrc,temp,1024);
		if(r > 0){//读到了
			write(fdDst,temp,r);//读了多少写多少
		}else{//没读到       
			break;//结束循环
		}
	}
	close(fdDst);close(fdSrc);
	printf("拷贝完毕!\n");
	system("ls");//调命令
}
