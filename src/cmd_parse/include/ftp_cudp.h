#ifndef FTP_CUDP_H
#define FTP_CUDP_H
#include "ftp_task.h"

class FtpCudp:public FtpTask{
public:
	void Parse(std::string type, std::string msg);
	FtpCudp(){}
	~FtpCudp(){}
private:
};

#endif