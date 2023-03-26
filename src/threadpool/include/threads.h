#ifndef __THREAD__
#define __THREAD__
#include<list>
#include<mutex>
#include<event2/event.h>
#include "xtask.h"
class XThread
{
public:
	void Start();

	void Main();	

	//安装线程，初始化event_base和管道监听事件用于激活
	bool Setup();

	//收到主线程发出的激活消息（线程池的分发）
	void Notify(evutil_socket_t fd,short which);

	void Activate();

	void AddTask(XTask* t);

	XThread();

	~XThread();
	
	int id = 0;
public:
	int notify_send_fd = 0;
	struct event_base* base = 0;
	
	std::list<XTask*> tasks;
	std::mutex tasks_mutex;

};
#endif
