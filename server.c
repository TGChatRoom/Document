//聊天室服务器端
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

//定义用户个人信息
struct user
{
    //存储服务器给用户分配的ID
    int ID;
    //存储用户登陆密码
    char PassWord[30];
    //存储客户端的socket描述符
    int ClientSockfd;
    //存储用户昵称
    char Gender[10];
    //存储用户性别
    char Gender[10];
    //存储用户籍贯
    char BirthPlace[30];
    //存储用户黑名单
    int BlockID[10];
    //存储用户在线状态，0表示不在线，1表示在线
    int Online;
}

//记录客户端ID，最大并发数为100
int c[100] = {0};

//记录目前有多少个用户在线(包括正在注册的用户)，也即数组的下标
int size = 0;

//记录服务器socket
int ServerSockfd = 0;

//记录服务器IP号
char *IP = "127.0.0.1"
  
//记录服务器端口号
 short PORT = 8886;

//*************************************************************
//@Function Name: void InitServer()
//@Parameter [in] : int a—
//@Parameter [out] : int b—
//@Parameter [in,out] : int c—
//@Description: 初始化服务器，使用TCP协议
//@Return Value:  无返回值
// 为1，表示：
// 为0，表示：
//*************************************************************
void InitServer(void)
{
    /*打印输出服务器开始工作*/
    printf("聊天室服务器开始启动...");
    
    /*创建socket*/
    ServerSockfd = socket(AF_INET, SOCK_STREAM, 0);
    //如果失败则打印相关错误信息并退出
    if(ServerSockfd == -1)
    {
        perror("创建服务器socket失败");
        printf("服务器启动失败\n");
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
    addr.sin_addr.s_addr = inet_addr(IP);
    
    /*绑定socket和通信地址*/
    //如果错误就打印相关信息并退出
    if(bind(ServerSockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        perror("绑定失败");
        printf("服务器启动失败\n");
        exit(-1);
    }
    //否则打印绑定成功信息
    printf("成功绑定\n");
    
    /*设置监听*/
    //如果错误就打印相关错误信息并退出
    if(listen(ServerSockfd, 100) == -1)
    {
        perror("设置监听失败");
        printf("服务器启动失败\n");
        exit(-1);
    }
    //否则打印设置监听成功
    printf("设置监听成功\n");
    printf("初始化服务器成功\n");
}

//*************************************************************
//@Function Name: void* ServiceThread(void* p)
//@Parameter [in] : int a—
//@Parameter [out] : int b—
//@Parameter [in,out] : int c—
//@Description: 服务器端线程服务程序。
//@Return Value:  
// 为1，表示：
// 为0，表示：
//*************************************************************
void* ServiceThread(void *p)
{
    /*记录客户端的sockefd*/
    int ClientSockfd = *(int*)p;
    
    /*定义每次消息发送字节数不能超过100个字符*/
    char Msg[100] = {0};
    
    /*发送欢迎词以及询问是否登陆还是注册*/
    char* q = "欢迎使用XXX聊天室";
    strncpy(Msg, q, 100);
    send(ClientSockfd, Msg, strlen(Msg), 0);
    q = "SignIn or SignUp?";
    strncpy(Msg, q, 100);
    send(ClientSockfd, Msg, strlen(Msg), 0);
    
    /*阻塞接受客户端发送过来的数据*/
    int ret = 0;
    ret = recv(ClientSockfd, Msg, sizeof(Msg), 0);
    //如果小于0，则表示接受错误，打印相关信息
    if(ret < 0)
    {
        perror("接受错误");
        return (void*)-3;
    }
    //如果等于0，则表示客户端断开连接，打印相关信息
    else if(ret == 0)
    {
        printf("客户端断开连接！\n");
        //减去此客户端并退出线程
    }
    else
    {
        printf("客户端说：%s\n", Msg);
    }  
}

//*************************************************************
//@Function Name: void Service(void)
//@Parameter [in] : int a—
//@Parameter [out] : int b—
//@Parameter [in,out] : int c—
//@Description: 服务器端服务程序。
//@Return Value:  无返回值
// 为1，表示：
// 为0，表示：
//*************************************************************
void Service(void)
{
    printf("服务器开始服务\n");
    while(1)
    {
        /*存储客户端的通信地址*/
        struct sockaddr_in fromaddr;
        socklen_t len = sizeof(fromaddr);
        
        /*接受客户端的登陆*/
        int ClientFd = accept(ServerSockfd, （struct sockaddr*）&fromaddr, &len);
        //如果错误则打印客户端连接出错
        //并继续下一次循环等待客户端连接
        if(ClientFd == -1)
        {
            printf("客户端连接出错\n");
            continue;
        }
        
        /*有客户端成功连接上服务器，记录客户端socket*/
        c[size] = ClientFd;
        size++;
        //打印客户端socket
        printf("客户端%d连接成功\n", ClientFd);
        
        /*开启线程，为此客户端服务*/
        pthread_t ClientPid;
        pthread_create(&ClientPid, 0, ServiceThread, &ClientFd);
    }
}

int main()
{
    //定义信号集处理，最多同时服务100个客户端
    singal(SIGINT, sig_close);
    
    //初始化服务器端
    InitServer();
    
    //启动服务
    service();
    
    return 0;
}





