#include "ftp_retr.h"
#include <iostream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <string>
#include <functional>
#include "global.h"
using namespace std;

// 下载

void FtpRetr::WriteWork(struct bufferevent *bev)
{
	if (!fp)
		return;
	int len = fread(buf, 1, sizeof(buf), fp);
	if (len <= 0)
	{
		ResCMD("226 Transfer complete\r\n");
		Close();
		return;
	}

	cout << "[" << len << "]" << flush;
	Send(buf, len);
}
void FtpRetr::EventWork(struct bufferevent *bev, short what)
{
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
		Close();
	}
	else if (what & BEV_EVENT_CONNECTED)
	{
		cout << "XFtpRETR BEV_EVENT_CONNECTED" << endl;
	}
}
void FtpRetr::Write(struct bufferevent *bev)
{
  function<void(FtpRetr *, bufferevent *)> obj = bind(&FtpRetr::WriteWork, this, bev);
  g_pool.submitTask(obj, this, bev);
}
void FtpRetr::Event(struct bufferevent *bev, short what)
{
  function<void(FtpRetr *, bufferevent *, short)> obj = bind(&FtpRetr::EventWork, this, bev, what);
  g_pool.submitTask(obj, this, bev, what);
}
void FtpRetr::Parse(std::string type, std::string msg)
{
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	path += "/";
	path += filename;
	std::cout << "path is: "<<path << std::endl;
	fp = fopen(path.c_str(), "rb");
	if (fp)
	{
		// 连接数据通道
		ConnectPORT();

		// 发送开始下载文件的指令
		ResCMD("150 File OK\r\n");
		// 触发写入事件
		bufferevent_trigger(bev, EV_WRITE, 0);
	}
	else
	{
		ResCMD("450 file open failed!\r\n");
	}
}