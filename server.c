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
