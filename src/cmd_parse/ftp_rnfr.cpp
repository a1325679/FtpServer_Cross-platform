#include "ftp_rnfr.h"
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpRnfr::Parse(std::string type, std::string msg)
{
  std::cout << "FTPRNFT CALLBACK" << std::endl;
  int pos = msg.find(" ");
  std::string file_name = msg.substr(pos + 1, msg.size() - pos - 3);
  if (cmdTask->curDir != "/")
  {
    std::string k = cmdTask->curDir.substr(1);
    file_name = k + "/" + file_name;
  }
  moveFile = file_name;
  std::cout << "FTPRNFT  moveFile : "<< moveFile<< std::endl;
  ResCMD("200 OK.");
}