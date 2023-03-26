#ifndef __XTASK__
#define __XTASK__
#include<string>
class XTask
{
public:
	virtual bool Init() {
    return true;
  }

  int sock = 0;
	int thread_id = 0;
  std::string ipaddr;
  int portFrom;
  // 初始化任务
  struct event_base* base = 0;
};
#endif
