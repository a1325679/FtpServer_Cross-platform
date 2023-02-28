#include "ftp_mkd.h"
#include "macor.h"
#include "log.h"
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpMkd::Parse(std::string type, std::string msg)
{
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  int head = msg.find(" ");
  std::string name = "." + cmdTask->curDir+"/"+ msg.substr(head + 1);
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), name.c_str());

  int ret;
#ifdef _WIN32
  if (access(name.c_str(), 0) == -1)
  {
    ret = mkdir(name.c_str());
  }
#else
  ret = mkdir(name.c_str(), 0777);
#endif
  if (ret == -1)
  {
    ResCMD("501 " + msg + " create failed." + "\r\n");
    return;
  }
  ResCMD("257 " + msg + " success create." + "\r\n");
  return;
}