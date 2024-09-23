#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>

int main(int argc, char *argv[]){
    //1.创建key
    key_t key = ftok(".", 'm');
    if(key == -1)printf("创建key失败 : %m\n"),exit(-1);
    printf("创建key成功\n");
    //2. 创建共享内存
    int shmid = shmget(key, 4096, IPC_CREAT | 0666);
    if(shmid == -1)printf("shmget error : %m\n"),exit(-1);
    printf("shmget success\n");
    //3. 连接/挂载共享内存 shmat attach
    int *shm_addr = shmat(shmid, NULL, 0);
    if(*shm_addr == -1)
        printf("shmat error\n"),exit(-1);
    printf("shmat success\n");
    //4. 写入数据
    while(1){
        printf("%d\n",*shm_addr);
        sleep(1);
    }
    //5. 断开连接
    shmdt(shm_addr);
    //6. 删除共享内存
    shmctl(shmid, IPC_RMID, 0);
    printf("Shared memory created and destroyed successfully!\n");
    return 0;
}