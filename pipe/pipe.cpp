#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT 0
#define OUTPUT 1

int main(){
    int fd[2];
    /*定义子进程号*/
    pid_t pid;
    char buf[256];
    int returned_count;
    /*创建无名管道*/
    pipe(fd);
}