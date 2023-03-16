#include "ftp_dele.h"
#include "macor.h"
#include "log.h"
#include <string>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <iostream>
// Dele text.txt\r\n
void FtpDele::Parse(std::string type, std::string msg)
{
  // std::cout << "FtpDELE COMMAND : " << msg << std::endl;
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());

  int pos = msg.find(" ");
  std::string file_name = rootDir + cmdTask->curDir+"/"+ msg.substr(pos + 1);
  // std::string file_name = msg.substr(pos + 1, msg.size() - pos - 1);
  // if (cmdTask->curDir != "/")
  // {
  //   std::string k = cmdTask->curDir.substr(1);
  //   file_name = k + "/" + file_name;
  // }
  if (remove(file_name.c_str()) == 0)
  {
    // printf("Removed %s.", file_name.c_str());
  }
  else
  {
    // perror("remove");
    log(NOTICE, "%s:%d %s:%d -> 删除文件 %s 失败", __FILE__, __LINE__, ipaddr.c_str(), portFrom,file_name.c_str());
  }
  ResCMD("250 " + file_name + " success delete." + "\r\n");
}