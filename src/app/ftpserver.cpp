#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h> //libevent头文件
#include <string.h>
#include <iostream>
#include <event2/thread.h>
#include <thread>
#ifndef _WIN32
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "log.h"
#include "read_conf.h"
#include "macor.h"
#include "ftp_factory.h"
#include "global.h"
#include "func.h"
using namespace std;

#define SPORT 8080
ThreadPool *g_pool = new ThreadPool();
void listen_cb(struct evconnlistener *e, evutil_socket_t s, struct sockaddr *a, int socklen, void *arg)
{
  event_base *base = (event_base *)arg;
  Task *task = FtpFactory::Get()->CreateTask();
  task->sock = s;
  task->base = base;

  struct sockaddr_in *sock = (struct sockaddr_in *)a;
  int port = ntohs(sock->sin_port);
#ifdef _WIN32 // windows上打印方式
  printf("ip:port  %s : %d", inet_ntoa(sock->sin_addr), port);
#else // linux上打印方式
  struct in_addr in = sock->sin_addr;
  char str[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN这个宏系统默认定义 16
  // 成功的话此时IP地址保存在str字符串中。
  inet_ntop(AF_INET, &in, str, sizeof(str));
  // printf("ip:port  %s : %d", str, port);
#endif
  task->ipaddr = str;
  task->portFrom = port;

  if (!task->Init())
  {
    log(NOTICE,"Locate","%s : %d 初始化失败", str, port);
    return;
  }
  log(NOTICE, "%s:%d %s:%d 已连接",__FILE__, __LINE__, task->ipaddr.c_str(), task->portFrom);
}
int main()
{
  g_pool->start(3);
// pool.setMode(PoolMode::MODE_CACHED);
// 创建libevent的上下文
#if _WIN32
  WSADATA wsa;
  WSAStartup(MAKEWORD(2, 2), &wsa);
  evthread_use_windows_threads();
#endif

  event_base *base = event_base_new();
  if (!base)
  {
    log(ERRORS,"Locate","even_base create failed! %s:%d", __FILE__, __LINE__);
  }

  Config *p_config = Config::GetInstance(); // 单例类
  if (p_config->Load("conf.conf") == false) // 把配置文件内容载入到内存
  {
    log(ERRORS,"Locate","Config Load failed ! %s:%d", __FILE__, __LINE__);
  }
  if (!MyLog::GetInstance()->Init("../log/error.log"))
  {
    std::cout << "Log init failed !" << std::endl;
    exit(1);
  }
  g_pool->submitTask(MyLog::PrintLogsThread, MyLog::GetInstance());
  InitSignal();
  unsigned short port = p_config->GetIntDefault("ListenPort0", 9090);

  // 监听端口
  // socket ，bind，listen 绑定事件
  sockaddr_in sin;
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  evconnlistener *ev = evconnlistener_new_bind(base,                                      // libevent的上下文
                                               listen_cb,                                 // 接收到连接的回调函数
                                               base,                                      // 回调函数获取的参数 arg
                                               LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, // 地址重用，evconnlistener关闭同时关闭socket
                                               10,                                        // 连接队列大小，对应listen函数
                                               (sockaddr *)&sin,                          // 绑定的地址和端口
                                               sizeof(sin));
  log(NOTICE,"%d 初始化完成,FTP服务器启动,%d端口已开启监听连接",getpid(),port);
  // 事件分发处理
  if (base)
  {
    int ret = event_base_dispatch(base);
  }
  if (ev)
    evconnlistener_free(ev);
  if (base)
    event_base_free(base);
  return 0;
}