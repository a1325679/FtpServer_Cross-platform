#include "ftp_rnto.h"
#include "macor.h"
#include "log.h"
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <fstream>
#include "cstdlib"
#else
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpRnto::Parse(std::string type, std::string msg)
{
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());

  int pos = msg.find(" ");
  std::string file_name = msg.substr(pos + 1);
  file_name = rootDir + curDir + file_name;
  // if (file_name[0] == '/')
  // {
  //   file_name = file_name.substr(1);
  // }
#ifdef _WIN32
  std::string cmd = "move ";
  cmd += moveFile;
  cmd += " ";
  cmd += file_name;
  MoveFileA(moveFile.c_str(), file_name.c_str());
#else
  rename(moveFile.c_str(), file_name.c_str());
#endif
  std::cout << "moveFile : " << moveFile << " file_name : " << file_name << "\n";
  ResCMD("250 move success .");
}