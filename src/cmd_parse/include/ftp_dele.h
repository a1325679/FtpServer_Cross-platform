#ifndef FTP_DELE_H
#define FTP_DELE_H
#include "ftp_task.h"
class FtpDele:public FtpTask{
public:
  virtual void Parse(std::string type, std::string msg);
  FtpDele(){}
  ~FtpDele(){}
private:
};
#endif