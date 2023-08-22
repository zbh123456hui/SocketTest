#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main(int argc, const char** argv) {
    int shmid;
    srand((unsigned int)getpid());
    shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
    if(shmid==-1){
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    void* shared_memory=(void*)0;
    shared_memory=shmat(shmid,(void*)0,0);

    return 0;
}