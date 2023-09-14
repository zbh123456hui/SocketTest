#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char** argv) {
    /*
        1、创建套接字
        2、绑定地址信息
        3、收发数据
        4、关闭套接字
    */

    int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd<0){
        return 0;
    }

    //addr: 服务器端绑定的地址信息结构，保存着服务端需要的ip地址和端口
    struct sockaddr_in addr;
    //填充地址类型，后续bind函数解析了地址类型之后，就知道传入的是哪一个数据结构了
    addr.sin_family=AF_INET;
    //填充端口，一定要注意将主机字节序转化为网络字节序
    addr.sin_port=htons(8080);
    //填充ip地址
    //addr.sin_addr.s_addr: 接受的是无符号32位的整数（IP地址）
    //in_addr_t inet_addr(const char *cp);
    //      参数：字符指针，接收一共点分十进制的字符串
    //      功能：将点分十进制的ip地址转换为无符号32位的整数
    //            将无符号32位的整数从主机字节序转换为网络字节序

    //容易犯错的地方：绑定了云服务器的公网ip，这个是万万不行的
    //               绑定了云服务器的私网io地址还可以
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");//0.0.0.0: 绑定本机的任意网卡

    int ret=bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret<0){
        return 0;
    }

    while(1){
        char buf[1024]={0};
        struct sockaddr_in peer_addr;
        socklen_t peer_addrlen=sizeof(peer_addr);

        recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&peer_addr,&peer_addrlen);
        printf("buf is : %s from %s, %d\n",buf,inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));

        //要向客户端发送数据
        memset(buf,'\0',sizeof(buf));
        sprintf(buf,"hello, %s: %d, I am server",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
        sendto(sockfd,buf,strlen(buf)-1,0,(struct sockaddr*)&peer_addr,sizeof(peer_addr));
    }

    while(1){
        sleep(1);
    }

    return 0;
}