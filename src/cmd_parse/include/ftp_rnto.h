#ifndef FTP_RNTO_H
#define FTP_RNTO_H
#include "ftp_task.h"
class FtpRnto:public FtpTask{
public:
	virtual void Parse(std::string type, std::string msg);
	FtpRnto(){}
	~FtpRnto(){}
private:
};
#endif