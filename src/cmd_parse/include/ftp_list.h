#ifndef FTP_LIST_H
#define FTP_LSIT_H
#include "ftp_task.h"
class FtpList:public FtpTask
{
	public:
		virtual void Parse(std::string type, std::string msg);
		virtual void Write(struct bufferevent *bev);
		virtual void Event(struct bufferevent *bev,short what);
		void WriteWork(struct bufferevent *bev);
		void EventWork(struct bufferevent *bev, short what);
    FtpList(){}
    ~FtpList(){}
};
#endif