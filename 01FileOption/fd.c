#include <unistd.h> //linux操作系统标准头文件
#include <string.h> //strlen
#include <stdio.h>
#include <stdlib.h>
int main(){
	//输出
	write(1,"大家晚上好\n",strlen("大家晚上好\n")+1);

	char 	name[20];
	char    temp[10];
	int 	age;
	double 	score;
	char buff[56];
	while(1){
		memset(name,0,20);
		write(1,"请输入名字:",strlen("请输入名字:")+1);
		read(0,name,sizeof(name));
		write(1,"请输入年龄:",strlen("请输入年龄:")+1);
		bzero(temp,10);
		read(0,temp,10);
		age = atoi(temp);
		write(1,"请输入成绩:",strlen("请输入成绩:")+1);
		bzero(temp,10);
		read(0,temp,10);
		score = atof(temp);
		memset(buff,0,56);
		sprintf(buff,"我是%s，今年%d岁,linux考了%f分\n",
			name,age,score);
		write(1,buff,strlen(buff)+1);
	}



	return 0;
}