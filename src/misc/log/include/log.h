#ifndef _LOG_H
#define _LOG_H
#include <list>
#include <string>
#include <stdarg.h>

class MyLog
{
public:
  bool programExit_;
  static MyLog *GetInstance();
  bool Init(const char *logfile);
  ~MyLog();
  bool Log(int level,const char *fmt, ...);
  bool AddMessage(std::string str);
  static void PrintLogsThread(void *args);
  std::string GetMessageQueueFrontElement()
  {
    std::string str = message_queue.front();
    message_queue.pop_front();
    return str;
  }
  bool IsEmptyMessageQueue()
  {
    return message_queue.empty();
  }
  FILE *GetFd()
  {
    return fd;
  }
  void flushMessage()
  {
    while (!message_queue.empty())
    {
      fputs(GetMessageQueueFrontElement().c_str(), GetFd());
      fflush(GetFd());
    }
  }
  class CGarge
  {
  public:
    CGarge()
    {
    }
    ~CGarge()
    {
      delete m_instance;
    }
  };

private:
  CGarge cg;
  MyLog();
  static MyLog *m_instance;
  std::list<std::string> message_queue;
  FILE *fd;
  int level;
};
#endif