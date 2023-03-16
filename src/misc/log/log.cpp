#include <iostream>
#include <string.h> //open
#include <time.h>   //localtime_r
#include <chrono>
#include <ctime>
#include <thread>
#include <chrono>
#include <ctime>
#ifndef _WIN32
#include <sys/time.h> //gettimeofday
#include <unistd.h>
#else
#include <Windows.h>
#endif
#include "read_conf.h"
#include "macor.h"
#include "log.h"
#include "func.h"
using namespace std;
static char err_levels[][20] = {
    {"stderr"}, // 0：控制台错误
    {"emerg"},  // 1：紧急
    {"alert"},  // 2：警戒
    {"crit"},   // 3：严重
    {"errors"}, // 4：错误
    {"warn"},   // 5：警告
    {"notice"}, // 6：注意
    {"info"},   // 7：信息
    {"debug"}   // 8：调试
};

MyLog *MyLog::m_instance = nullptr;
MyLog *MyLog::GetInstance()
{
  if (m_instance == nullptr)
  {
    if (m_instance == nullptr)
    {
      m_instance = new MyLog;
    }
  }
  return m_instance;
}
bool MyLog::Init(const char *logfile)
{
  fd = fopen(logfile, "a+");
  if (fd == nullptr)
  {
    return false;
  }
  level = Config::GetInstance()->GetIntDefault("LogLevel", 5);
  return true;
}
bool MyLog::AddMessage(std::string str)
{
  str += "\r\n";
  message_queue.push_back(str);
  // fputs(str.c_str(), fd);
  return true;
}
#define MAX_ERROR_STR 1024
// 2023/01/16 22:14:05 [notice] 16930: worker process 16930 启动并开始运行......!
bool MyLog::Log(int level, const char *fmt, ...)
{
  va_list args;
#ifdef _WIN32
  std::string str;
  time_t now = time(nullptr);
  tm *curr_tm = localtime(&now);
  char strcurrtime[40] = {0};
  strftime(strcurrtime, 40, "%Y/%m/%d %H:%M:%S ", curr_tm);
  str += strcurrtime;
  const char *s = err_levels[level];
  std::string errlevel = "[" + (std::string)s + "] ";
  str += errlevel;
  char c[8];
  std::thread::id this_id = std::this_thread::get_id();
  unsigned int t = *(unsigned int *)&this_id;
  sprintf(c, "%d: ", t);
  str += c;
#else
  struct timeval tv;
  struct tm tm;
  time_t sec;
  string str;
  memset(&tv, 0, sizeof(struct timeval));
  memset(&tm, 0, sizeof(struct tm));
  gettimeofday(&tv, NULL);
  sec = tv.tv_sec;
  localtime_r(&sec, &tm);
  tm.tm_mon++;
  tm.tm_year += 1900;
  char strcurrtime[40] = {0};
  sprintf(strcurrtime, "%4d/%02d/%02d %02d:%02d:%02d ", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  str += strcurrtime;
  const char *s = err_levels[level];
  std::string errlevel = "[" + (std::string)s + "] ";
  str += errlevel;
#endif

  char errstr[MAX_ERROR_STR + 1];
  va_start(args, fmt);
  vsprintf(errstr, fmt, args);
  va_end(args);
  str += errstr;
  if (level == 0)
  {
    std::cout << str << std::endl;
    return true;
  }
  if (level < this->level)
  {
    AddMessage(str);
  }
  return true;
}
void MyLog::PrintLogsThread(void *args)
{
  MyLog *t = (MyLog *)args;
  for (;;)
  {
    if (t->IsEmptyMessageQueue())
    {
      this_thread::sleep_for(1s);
    }
    else
    {
      // fwrite(t->GetMessageQueueFrontElement().c_str(), 1, t->GetMessageQueueFrontElement().size(), t->GetFd());
      string s = t->GetMessageQueueFrontElement().c_str();
      s.pop_back();
      fputs(s.c_str(), t->GetFd());
      fflush(t->GetFd());
      this_thread::sleep_for(1s);
    }
  }
}
MyLog::~MyLog()
{
  while (!message_queue.empty())
  {
    fputs(GetMessageQueueFrontElement().c_str(), GetFd());
    fflush(GetFd());
  }
  fclose(fd);
}
MyLog::MyLog() : programExit_(false)
{
}