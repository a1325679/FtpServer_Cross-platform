#include "ftp_cudp.h"
#include "macor.h"
#include "log.h"
#include <iostream>
#include <string>
using namespace std;
void FtpCudp::Parse(std::string type, std::string msg)
{
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());

  string path = cmdTask->curDir;
  if (path[path.size() - 1] == '/')
  {
    path = path.substr(0, path.size() - 1);
  }
  int pos = path.rfind("/");
  path = path.substr(0, pos);
  cmdTask->curDir = path;
  ResCMD("250 Directory success changed. \r\n");
}