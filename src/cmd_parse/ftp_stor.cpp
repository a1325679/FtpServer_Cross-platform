#include "ftp_stor.h"
#include "macor.h"
#include "log.h"
#include <iostream>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <functional>
#include "global.h"
#include <unistd.h>
using namespace std;
FtpStor::FtpStor() {}
FtpStor::~FtpStor()
{
}
// 解析协议
void FtpStor::Parse(std::string type, std::string msg)
{
  // 文件名
  if (msg.find("\r\n") != std::string::npos)
  {
    msg.pop_back();
    msg.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(), msg.c_str());

  int pos = msg.rfind(" ") + 1;
  string filename = msg.substr(pos);
  string path = cmdTask->rootDir;
  path += cmdTask->curDir;
  path += "/";
  path += filename;
  fp = fopen(path.c_str(), "wb+");
  if (fp)
  {
    // 连接数据通道
    ConnectPORT();

    // 发送开始接收文件的指令
    ResCMD("125 File OK\r\n");
    // 触发读取事件
    bufferevent_trigger(bev, EV_READ, 0);
  }
  else
  {
    ResCMD("450 file open failed!\r\n");
  }
}
void FtpStor::ReadWork(struct bufferevent *bev)
{
  // std::cout << "call FtpSTRO READ WORK"
  //           << "\n";
  if (!fp)
    return;
  for (;;)
  {
    int len = bufferevent_read(bev, buf, sizeof(buf));
    if (len <= 0)
      return;
    int size = fwrite(buf, 1, len, fp);
    fflush(fp);
    cout << "WRITE BYTES :<" << len << ":" << len << ">" << flush;
  }
  cout << "================================="
       << "\n";
}
void FtpStor::EventWork(struct bufferevent *bev, short what)
{
  // std::cout << "call FtpSTRO Event WORK"
  //           << "\n";
  //  如果对方网络断掉，或者机器死机有可能收不到BEV_EVENT_EOF数据
  if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT))
  {
    // cout << "XFtpSTOR BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT" << endl;
    log(NOTICE, "%s:%d %s:%d -> FtpSTOR BEV_EVENT_EOF | BEV_EVENT_ERROR |BEV_EVENT_TIMEOUT", __FILE__, __LINE__, ipaddr.c_str(), portFrom);
    Close();
    ResCMD("226 Transfer complete\r\n");
  }
  else if (what & BEV_EVENT_CONNECTED)
  {
    // cout << "XFtpSTOR BEV_EVENT_CONNECTED" << endl;
    log(NOTICE, "%s:%d %s:%d -> FtpSTOR BEV_EVENT_CONNECTED", __FILE__, __LINE__, ipaddr.c_str(), portFrom);
  }
}
void FtpStor::Read(struct bufferevent *bev)
{
  function<void(FtpStor *, bufferevent *)> obj = bind(&FtpStor::ReadWork, this, bev);
  g_pool->submitTask(obj, this, bev);
}
void FtpStor::Event(struct bufferevent *bev, short what)
{
  function<void(FtpStor *, bufferevent *, short)> obj = bind(&FtpStor::EventWork, this, bev, what);
  g_pool->submitTask(obj, this, bev, what);
}