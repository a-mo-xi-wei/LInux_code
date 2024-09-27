/*************************************************************************
    > File Name: client.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月25日 星期三 16时41分21秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int fd;
void hand(int s){
	if(2 == s){
		//5 断开连接
		close(fd);
		printf("bye bye !\n");
		exit(1);
	}
}

int main(){
	signal(2,hand);
	//1 创建socket
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd) printf("创建socket失败:%m!\n"),exit(-1);
	printf("创建socket成功!\n");
	//2 协议地址簇
	struct sockaddr_in addr={0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip地址 注意字符串转网络字节序
	addr.sin_port = htons(8888);//端口号 用1W左右的  大小端转换
	//3 连接服务器
	int r = connect(fd,(struct sockaddr*)&addr,sizeof addr);
	if(-1 == r) printf("连接服务器失败:%m!\n"),exit(-1);
	printf("连接服务器成功!\n");

	//4 通信
	char buff[1024];
	char temp[1024];
	while(1){
		printf("请输入要发送给服务器的数据:");
		scanf("%s",buff);
		r = send(fd,buff,strlen(buff),0);
		printf("发送%d字节数据到服务器!\n",r);
		r = recv(fd,temp,1023,0);
		if(r>0){
			temp[r] = '\0';
			printf("服务器回复:%s\n",temp);
		}
	}
}

