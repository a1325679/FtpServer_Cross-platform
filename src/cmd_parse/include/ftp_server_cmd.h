#ifndef _FTP_SERVER_CMD_
#define _FTP_SERVER_CMD_
#include "ftp_task.h"
#include <map>
class FtpServerCMD : public FtpTask
{
public:
	// 初始化任务
	virtual bool Init();
	virtual void Read(struct bufferevent* bev);
	virtual void Event(struct bufferevent *bev, short what);
	// 注册命令处理对象 不需要考虑线程安全，调用时还未分发到线程
	void Reg(std::string, FtpTask *call);
	FtpServerCMD();
	~FtpServerCMD();
	std::map<std::string, FtpTask *> calls;

private:
	// 注册的处理对象
	//std::map<std::string, XFtpTask *> calls;
	// 用来做空间清理
	std::map<FtpTask *, int> calls_del;
};

#endif