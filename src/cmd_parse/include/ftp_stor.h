
#include "ftp_task.h"

// 上传文件
class FtpStor : public FtpTask
{
public:
  // 解析协议
  virtual void Parse(std::string type, std::string msg);
  virtual void Read(struct bufferevent *bev);
  virtual void Event(struct bufferevent *bev, short what);

  void ReadWork(struct bufferevent *bev);
  void EventWork(struct bufferevent *bev, short what);

private:
  FILE *fp = 0;
  char buf[1024] = {0};
};
