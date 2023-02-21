#ifndef FTP_MKD_H
#define FTP_MKD_H
#include "ftp_task.h"
class FtpMkd:public FtpTask{
public:
	virtual void Parse(std::string type, std::string msg);
	FtpMkd(){}
	~FtpMkd(){}
private:
};
#endif