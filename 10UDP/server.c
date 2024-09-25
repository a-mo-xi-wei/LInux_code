/*************************************************************************
    > File Name: server.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月25日 星期三 16时46分56秒
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
	int serverFd = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == serverFd){
		printf("创建socket失败:%m\n");
		return -1;
	}
	printf("创建socket成功!\n");

	//2 服务器协议地址簇
	struct sockaddr_in addr={0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.71.128");
	addr.sin_port=htons(9999);

	//3 绑定
	int r = bind(serverFd,(struct sockaddr*)&addr,sizeof addr);
	if(-1 == r) printf("绑定失败:%m!\n"),close(serverFd),exit(-1);
	printf("绑定成功!\n");

	//4 通信
	char buff[1024];
	struct sockaddr_in cAddr={0};
	int len = sizeof cAddr;
	while(1){
		//r = recv(serverFd,buff,1023,0);
		r = recvfrom(serverFd,buff,1023,0,
			(struct sockaddr*)&cAddr,&len);
		if(r > 0) {
			buff[r] = 0;//添加字符串结束符号 '\0'
			printf("%d:%s\n",r,buff);

			sendto(serverFd,"回复",strlen("回复"),0,
				(struct sockaddr*)&cAddr,sizeof cAddr);
		}
	}



	return 0;
}
