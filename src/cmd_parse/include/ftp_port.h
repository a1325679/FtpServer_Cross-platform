#ifndef FTP_PORT_H
#define FTP_PORT_H
#include "ftp_task.h"
class FtpPort:public FtpTask{
public:
  void Parse(std::string type, std::string msg);
  FtpPort(){}
  ~FtpPort(){}

private:
};
#endif