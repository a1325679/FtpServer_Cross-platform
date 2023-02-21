#ifndef FTP_CWD_H
#define FTP_CWD_H
#include "ftp_task.h"
class FtpCwd :
    public FtpTask
{
public:
    void Parse(std::string type, std::string msg);
		FtpCwd(){}
		~FtpCwd(){}
};

#endif