#ifndef _FTP_TASK_
#define _FTP_TASK_

#include "task.h"
#include <string>

struct bufferevent;
class FtpTask : public Task
{
public:
	std::string curDir = "/";
	//std::string rootDir = ".";
  std::string rootDir = "../file";
  std::string moveFile;
  // PORT 数据通道的IP和端口
  std::string ip = "";
	int port = 0;

	// 命令通道
	FtpTask *cmdTask = 0;

	// 解析协议
	virtual void Parse(std::string type, std::string msg) {}
	// 回复cmd消息
	void ResCMD(std::string msg);

	// 用来发送建立了连接的数据通道
	void Send(std::string data);
	void Send(const char *data, int datasize);

	// 连接数据通道
	void ConnectPORT();
	void Close();
	virtual void Read(struct bufferevent *bev) {}
	virtual void Write(struct bufferevent *bev) {}
	virtual void Event(struct bufferevent *bev, short what) {}
	void SetCallback(struct bufferevent *bev);
	bool Init() { return true; }

protected:
	static void ReadCB(bufferevent *bev, void *arg);
	static void WriteCB(bufferevent *bev, void *arg);
	static void EventCB(struct bufferevent *bev, short what, void *arg);
	std::string GetListData(std::string path);
	// 命令bev
	struct bufferevent *bev = 0;
	FILE *fp = 0;
};

#endif