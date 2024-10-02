/*************************************************************************
    > File Name: server.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月25日 星期三 16时37分01秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int clientFd;
int serverFd;
void hand(int s){
	if(2 == s){
		//7 断开连接
		close(clientFd);
		close(serverFd);
		printf("bye bye 了勾八!\n");
		exit(1);
	}
}

int main(){
	signal(2,hand);
	//1 创建socket
	serverFd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == serverFd) printf("创建socket失败:%m!\n"),exit(-1);
	printf("创建socket成功!\n");
	//2 协议地址簇
	struct sockaddr_in addr={0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip地址 注意字符串转网络字节序
	addr.sin_port = htons(8888);//端口号 用1W左右的  
	//3 绑定
	int r = bind(serverFd,(struct sockaddr*)&addr,sizeof addr); 
	if(-1 == r) printf("绑定失败:%m!\n"),close(serverFd),exit(-1);
	printf("绑定成功!\n");
	//4 监听
	r = listen(serverFd,100);//最大容量为100
	if(-1 == r) printf("监听失败:%m!\n"),close(serverFd),exit(-1);
	printf("监听成功!\n");
	//5 接受客户端连接
	struct sockaddr_in cAddr = {0};//用来接收客户端的协议地址簇
	int len = sizeof cAddr;
	clientFd = accept(serverFd,(struct sockaddr*)&cAddr,&len);
	if(-1 == clientFd) printf("服务器崩溃:%m\n"),close(serverFd),exit(-1);
	printf("接受客户端连接成功:%d %s %u\n",clientFd,inet_ntoa(cAddr.sin_addr),cAddr.sin_port);
	//6 通信
	char buff[1024];
	int n=0;
	char temp[1024];
	while(1){
		r = recv(clientFd,buff,1023,0);
		if(r > 0) {
			buff[r] = '\0';//添加字符串结束符号 '\0'
			printf("%d:%s\n",r,buff);
			sprintf(temp,"%d-%s",n++,buff);
			send(clientFd,temp,strlen(temp),0);
		}
	}
}

