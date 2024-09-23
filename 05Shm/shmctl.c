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
    
#if 0
    //3. 删除共享内存
    int r = shmctl(shmid, IPC_RMID, NULL);
    if(r == -1)printf("shmctl error : %m\n"),exit(-1);
    printf("Shared memory created and destroyed successfully!\n");
#else
    //4.获取共享内存状态
    struct shmid_ds ds = {0};
    int r = shmctl(shmid, IPC_STAT, &ds);
    if(r == -1)printf("获取共享内存状态失败 : %m\n"),exit(-1);
    printf("获取共享内存状态成功\n");
    printf("挂载数：%ld\n",ds.shm_nattch);
    printf("创建进程id：%d\n",ds.shm_cpid);
    printf("大小：%ld\n",ds.shm_segsz);
#endif
    return 0;
}