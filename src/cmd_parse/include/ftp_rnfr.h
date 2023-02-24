#ifndef FTP_RNFR_H
#define FTP_RNFR_H
#include "ftp_task.h"
class FtpRnfr:public FtpTask{
public:
	virtual void Parse(std::string type, std::string msg);
	FtpRnfr(){}
	~FtpRnfr(){}
private:
};
#endif