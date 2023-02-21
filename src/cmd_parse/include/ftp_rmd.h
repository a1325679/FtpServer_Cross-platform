#ifndef FTP_RMD_H
#define FTP_RMD_H
#include "ftp_task.h"
class FtpRmd:public FtpTask{
public:
	virtual void Parse(std::string type, std::string msg);
	FtpRmd(){}
	~FtpRmd(){}
private:
};
#endif