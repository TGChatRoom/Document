/*聊天室客户端头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

/*准备工作*/
//定义客户端socket变量
int ClientSockfd = 0;
//记录服务器端IP号
char *ServerIP = "127.0.0.1";
//记录服务器端口号
short PORT = 8886;

//*************************************************************
//@Function Name: void ClientInit(void)
//@Description: 客户端初始化程序。
//@Return Value:  无返回值
//*************************************************************
/*1. 启动客户端，连接服务器*/
void ClientInit(void)
{
    /*打印输出客户端开始启动*/
    printf("客户端开始启动");
    
    /*创建客户端socket*/
    ClientSockfd = socket(AF_INET, SOCK_STREAM, 0);
    //如果失败则打印相关错误信息并退出
    if(ClientSockfd == -1)
    {
        perror("创建客户端socket失败");
        printf("客户端启动失败");
        exit(-1);
    }
    
    /*准备通信地址*/
    //网络通信地址结构
    struct sockaddr_in addr;
    //协议簇
    addr.sin_family = AF_INET;
    //端口
    addr.sin_port = htons(PORT);
    //服务器端IP地址
    addr.sin_addr.s_addr = inet_addr(ServerIP);
    
    /*尝试连接服务器*/
    //如果出错则打印相关错误信息
    if(connect(ClientSockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        perror("无法连接到服务器");
        printf("客户端启动失败\n");
        exit(-1);
    }
    printf("客户端启动成功\n");
}

int main(void)
{
    ClientInit();
}
  
