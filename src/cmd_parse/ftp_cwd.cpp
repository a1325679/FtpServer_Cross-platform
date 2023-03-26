#include "ftp_cwd.h"
#include "macor.h"
#include "log.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

static int IsFileExist(const char* path) {
  return !access(path, F_OK);
}
void FtpCwd::Parse(std::string type, std::string msg)
{
  // 取出命令中的路径
  // CWD test\r\n
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());

  int pos = msg.rfind(" ") + 1;
  // 去掉结尾的\r\n
  string path = msg.substr(pos);  
  // cmdTask->curDir = path+"/";
  if (path[0] == '/') //局对路径
  {
    cmdTask->curDir = path+"/";
  }
  else
  {
    if (cmdTask->curDir[cmdTask->curDir.size() - 1] != '/')
      cmdTask->curDir += "/";
    cmdTask->curDir += path + "/";
  }
  std::string dir_path = cmdTask->rootDir + cmdTask->curDir;
  if(!IsFileExist(dir_path.c_str())){
    mkdir(dir_path.c_str(), 0777);
  }

  std::cout<<"============================="<<cmdTask->curDir<<std::endl;
	ResCMD("250 Directory succes chanaged.\r\n");
  // cmdTask->curDir +=
}