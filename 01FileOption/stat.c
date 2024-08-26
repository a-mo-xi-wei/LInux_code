
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc,char* argv[]){
	if(argc < 2){
		printf("请命令行输入文件名!\n");
		exit(-1);//结束当前进程
	}

	struct stat st;
	int ret = stat(argv[1],&st);
	if(-1 == ret) printf("获取文件状态失败:%m\n"),exit(-1);

	printf("最终修改时间:%ld %ld\n",st.st_mtime,st.st_ctime);
	struct tm* t = localtime(&st.st_mtime);
	printf("%d-%d-%d %d:%d:%d 星期:%d\n",
		t->tm_year + 1900,t->tm_mon + 1,t->tm_mday,
		t->tm_hour,t->tm_min,t->tm_sec,
		t->tm_wday);
	printf("文件类型:%d\n",st.st_mode);
	if(S_ISDIR(st.st_mode)){
		printf("%s是个目录!\n",argv[1]);
	}else{
		printf("%s是个普通文件!\n",argv[1]);
	}
	printf("文件大小:%ld\n",st.st_size);
}
