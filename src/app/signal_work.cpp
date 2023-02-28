#include <signal.h>
#include <unistd.h>
#include <iostream>
#include "macor.h"
#include "log.h"
#include "func.h"
void sigcb(int signo)
{
  switch (signo)
  {
  case SIGHUP:
    log(NOTICE,"%d 接收到 SIGHUP 信号,FTP服务已终止！",getpid());
    ClearWork();
    exit(0);
    break;
  case SIGINT:
    log(NOTICE, "%d 接收到 SIGINT 信号,FTP服务已终止！", getpid());
    ClearWork();
    exit(0);

    break;
  case SIGQUIT:
    log(NOTICE, "%d 接收到 SIGQUIT 信号,FTP服务已终止！",getpid());
    ClearWork();
    exit(0);
    break;
  }
}
bool InitSignal()
{
  signal(SIGHUP, sigcb);
  signal(SIGINT, sigcb);
  signal(SIGQUIT, sigcb);
  return true;
}