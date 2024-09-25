/*************************************************************************
    > File Name: client.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月25日 星期三 16时47分54秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main(){
	//1 创建socket
	int fd = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == fd){
		printf("创建socket失败:%m\n");
		return -1;
	}
	printf("创建socket成功!\n");

	//2 服务器协议地址簇
	struct sockaddr_in addr={0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.71.128");
	addr.sin_port=htons(9999);

	//3 通信
	char buff[1024];
	char temp[1024];
	int r;
	while(1){
		printf("你想发什么:");
		scanf("%s",buff);

		sendto(fd,buff,strlen(buff),0,
			(struct sockaddr*)&addr,sizeof addr);
		memset(temp,0,1024);
		//r = recv(fd,temp,1023,MSG_DONTWAIT);
		r = recv(fd,temp,1023,0);
		printf("r:%d,temp:%s\n",r,temp);
	}



	return 0;
}
