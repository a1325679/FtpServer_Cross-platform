#include "ftp_rnto.h"
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
  int pos = msg.find(" ");
  std::string file_name = msg.substr(pos + 1, msg.size() - pos - 3);
  if (file_name[0] == '/')
  {
    file_name = file_name.substr(1);
  }
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