#include "ftp_pwd.h"
#include <iostream>
#include <string>
#include "log.h"
#include "macor.h"
void FtpPWD::Parse(std::string type, std::string msg)
{
  if(msg.find("\r\n")!=std::string::npos) {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());
  std::string resmsg = "";
  resmsg += "257 \"";
  resmsg += cmdTask->curDir;
  resmsg += "\" is current dir. \r\n";
  ResCMD(resmsg);
}