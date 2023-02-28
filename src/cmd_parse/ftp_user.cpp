#include "ftp_user.h"
#include "log.h"
#include "macor.h"
#include <iostream>
using namespace std;
// 解析协议
void FtpUser::Parse(std::string type, std::string msg)
{
  // cout << "XFtpUSER::Parse " << type << " " << msg << endl;
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());
  ResCMD("230 Login successful.\r\n");
}

FtpUser::FtpUser()
{
}

FtpUser::~FtpUser()
{
}
