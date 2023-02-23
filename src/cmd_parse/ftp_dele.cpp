#include "ftp_dele.h"
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
  std::cout << "FtpDELE COMMAND : " << msg << std::endl;
  int pos = msg.find(" ");
  std::string file_name = msg.substr(pos + 1, msg.size() - pos - 2-1);
  if (cmdTask->curDir != "/")
  {
    std::string k = cmdTask->curDir.substr(1);
    file_name = k + "/" + file_name;
  }
  if (remove(file_name.c_str()) == 0)
  {
    printf("Removed %s.", file_name.c_str());
  }
  else
  {
    perror("remove");
  }
  ResCMD("250 " + file_name + " success delete." + "\r\n");
}