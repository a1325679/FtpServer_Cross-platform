#ifndef _USER_H
#define _USER_H
#include "ftp_task.h"
class FtpUser:public FtpTask
{
public:
	//解析协议
	virtual void Parse(std::string type, std::string msg);
	FtpUser();
	~FtpUser();
};
#endif