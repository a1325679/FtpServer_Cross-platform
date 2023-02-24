#include "ftp_rnto.h"
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpRnto::Parse(std::string type, std::string msg)
{
  int pos = msg.find(" ");
  std::string file_name = msg.substr(pos + 1, msg.size() - pos - 3);
  // if (cmdTask->curDir != "/")
  // {
  //   std::string k = cmdTask->curDir.substr(1);
  //   file_name = k + "/" + file_name;
  // }
  if(file_name[0]=='/') {
    file_name = file_name.substr(1);
  }
  std::cout<<"moveFile : "<<moveFile <<" file_name : "<<file_name<<"\n"; 
  rename(moveFile.c_str(),file_name.c_str());
  ResCMD("250 move success .");
}