#ifndef FTP_RETR_H
#define FTP_RETR_H
#include "ftp_task.h"
class FtpRetr:public FtpTask{
public:
	virtual void Parse(std::string type, std::string msg);
	virtual void Write(struct bufferevent *bev);
	virtual void Event(struct bufferevent *bev, short what);
  void WriteWork(struct bufferevent *bev);
  void EventWork(struct bufferevent *bev, short what);
  FtpRetr(){}
	~FtpRetr(){}
private:
	FILE *fp = 0;
	char buf[1024] = {0};
};

#endif