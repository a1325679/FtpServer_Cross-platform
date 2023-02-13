#ifndef FTP_PWD_H
#define FTP_PWD_H
#include "ftp_task.h"
class FtpPWD :
    public FtpTask
{
public:
    virtual void Parse(std::string type, std::string msg);
		FtpPWD(){}
		~FtpPWD(){}
};
#endif
