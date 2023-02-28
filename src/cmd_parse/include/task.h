#ifndef _TASK_
#define _TASK_
#include<string>
struct event_base;
class Task
{
public:
	struct event_base* base = 0;
  std::string ipaddr;
  int portFrom;
  int sock = 0;
  int thread_id = 0;
	//初始化任务
	virtual bool Init() = 0;
};

#endif
