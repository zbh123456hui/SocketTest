#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char** argv) {
    int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0){
        perror("socket");
        return 0;
    }
    /*
        ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
                        const struct sockaddr* dest_addr, socklen_t addrlen)
    */
    const char* str="I am client ...\n";

    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8080);//这里填充的是服务端的端口，因为数据是发送到服务端的
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");//填充服务端的ip

    sendto(sockfd,str,strlen(str),0,(struct sockaddr*)&addr,sizeof(addr));
    while(1){
        char buf[1024];
        bzero(&buf, sizeof(buf));
        scanf("%s", buf);
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));

        //相当于不要recvfrom函数返回服务端的地址信息，以及地址信息的长度
        //因为客户端是清除服务端的地址信息的
        recvfrom(sockfd,&buf,sizeof(buf),0,NULL,NULL);
        printf("buf is %s\n",buf);
        sleep(1);
    }

    return 0;
}