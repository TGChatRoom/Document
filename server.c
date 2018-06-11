//定义用户个人信息
struct user
{
    //存储服务器给用户分配的ID
    int ID;
    //存储用户登陆密码
    char PassWord[30];
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

//记录目前有多少个用户在线，也即数组的下标
int size;

//记录服务器socket
int ServerSockfd;

//记录服务器IP号
char *IP = "122.80.21.141"
  
//记录服务器端口号
 short PORT = 8886;

//*************************************************************
//@Function Name: void InitServer()
//@Parameter [in] : int a—
//@Parameter [out] : int b—
//@Parameter [in,out] : int c—
//@Description: 初始化服务器，使用TCP协议
//@Return Value:
// 为1，表示：
// 为0，表示：
//*************************************************************
void InitServer()
{
    //打印输出服务器开始工作
    printf("聊天室服务器开始启动...");
    
    //创建socket
    ServerSockfd = socket(PF_INET, SOCK_STREAM, 0);
    //如果失败则打印相关错误信息并退出
    if(ServerSockfd == -1)
    {
        perror("创建服务器socket失败");
        printf("服务器启动失败\n");
        exit(-1);
    }
    
    //准备通信地址
    
}


int main()
{
    //定义信号集处理，最多同时服务100个客户端
    singal(SIGINT, sig_close);
    
    //初始化服务器端
    init();
    
    //启动服务
    service();
    
    return 0;
}
