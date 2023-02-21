#include "ftp_mkd.h"
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
  int head = msg.find(" ");
  int back = msg.find("\r\n");
  std::string name = msg.substr(head + 1, back - head - 1);
  int ret;
#ifdef _WIN32
  if (access(name.c_str(), 0) == -1)
  {
    ret = mkdir(name.c_str());
  }
#else
  int ret = mkdir(name.c_str(), 0777);
#endif
  if (ret == -1)
  {
    ResCMD("501 " + msg + " create failed." + "\r\n");
    return;
  }
  ResCMD("257 " + msg + " success create." + "\r\n");
  return;
}