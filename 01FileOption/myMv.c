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
		printf("请命令行输入三个!\n");
		exit(-1);//结束当前进程
	}

	struct stat st;
	int ret = stat(argv[2],&st);
	if(-1 == ret) printf("获取文件状态失败:%m\n"),exit(-1);

	int fdSrc = open(argv[1],O_RDONLY);
	if(-1 == fdSrc) printf("打开待拷贝文件失败:%m\n"),exit(-1);
	printf("打开待拷贝文件%m\n");
	int fdDst;

	if(S_ISDIR(st.st_mode)){//移动  拷贝到指定目录后删除当前源
		char srcName[56] = {0};
		int k=0;
		char* p = argv[1];
		int len = strlen(argv[1]);
		p+=len-1;
		while(*p!='/'){
			srcName[k] = *p;
			p--;
			k++;
		}
		
		char t;
		for(int i=0;i<k/2;i++){
			
			t = srcName[i];
			srcName[i] = srcName[k-i-1];
			srcName[k-i-1] = t;
		}
		printf("srcName:%s\n",srcName);

		char dstName[256] = {0};
		sprintf(dstName,"%s/%s",argv[2],srcName);
		fdDst = open(dstName,O_WRONLY|O_CREAT,0666);
		if(-1 == fdDst) printf("创建拷贝后文件%s失败:%m\n",dstName),exit(-1);
		printf("创建拷贝后文件%m\n");
		
	}
	else{//重命名  复制到当前目录后删除当前源
		fdDst = open(argv[2],O_WRONLY|O_CREAT,0666);
		if(-1 == fdDst) printf("创建拷贝后文件失败:%m\n"),exit(-1);
		printf("创建拷贝后文件%m\n");
	}

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

	unlink(argv[1]);//删当前源
}
