/*************************************************************************
    > File Name: msgA.c
    > Author: 威桑
    > Mail: 1428206861@qq.com 
    > Created Time: 2024年09月23日 星期一 20时56分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define BUFSIZE 100
#define TYPE 1
void syserr(char* str){
	perror(str);
	exit(1);
}
int main(int argc,char* argv[]){
	 //1.创建key
    key_t key = ftok(".", 'q');
    if(key == -1)printf("创建key失败 : %m\n"),exit(-1);
    printf("创建key成功\n");
    //获取消息队列
    int msgid = msgget(key, IPC_CREAT | 0666);
    if(msgid == -1)printf("msgget error : %m\n"),exit(-1);
    printf("msgget success\n");
    
    //创建消息体
    struct msgbuf{
        long mtype;
        char mtext[BUFSIZ];
    }msg;
    //发送消息
    int ret;
    while(1){
        printf("请输入消息类型: ");
        scanf("%ld",&msg.mtype);
        printf("请输入消息内容: ");
        scanf("%s",msg.mtext);
        ret = msgsnd(msgid,&msg,sizeof(msg.mtext),IPC_NOWAIT);
        if(ret == -1)syserr("msgsnd failed");
        printf("ret : %d\n",ret);        
    }
    if (msgctl(msgid, IPC_RMID, NULL) == -1)syserr("msgctl failed");
}
