#include"threads.h"
#include<thread>
#include<iostream>
#include<event2/event.h>
#include"xtask.h"
#ifndef _WIN32
#include<unistd.h>
#endif

void XThread::Start()
{
	Setup();
	//启动线程
	std::thread th(&XThread::Main, this);
	//断开与主线程联系
	th.detach();
}

void XThread::Main() {
	std::cout << id << "XThread::Main() begin" << std::endl;
	event_base_dispatch(base);
	event_base_free(base);
	std::cout << id << " XThread::Main() end" << std::endl;
}
static void NotifyCB(evutil_socket_t fd, short which,void* args) {
	XThread* t = (XThread*)args;
	t->Notify(fd, which);
}
//安装线程，初始化event_base和管道监听事件用于激活
bool  XThread::Setup() {
#ifdef _WIN32
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0) {
		std::cout << "evutil_socketpair failed!" << std::endl;
		return false;
	}
	evutil_make_socket_nonblocking(fds[0]);
	evutil_make_socket_nonblocking(fds[1]);
#else
	int fds[2];
	if (pipe(fds)) {
		std::cerr << "pipe_failed" << std::endl;
		return false;
	}
#endif

	notify_send_fd = fds[1];

	event_config* ev_conf = event_config_new();
	event_config_set_flag(ev_conf,EVENT_BASE_FLAG_NOLOCK);
	this->base = event_base_new_with_config(ev_conf);
	event_config_free(ev_conf);
	if (!base) {
		std::cerr << "event_base_new_with_config failed in thread!" << std::endl;
		return false;
	}
	event* ev = event_new(base, fds[0], EV_READ | EV_PERSIST, NotifyCB,this);
	event_add(ev,0);
	return true;
}

//收到主线程发出的激活消息（线程池的分发）
void  XThread::Notify(evutil_socket_t fd, short which) {
	//水平触发 只要没有接受完成，会再次进来
	char buf[2] = { 0 };
#ifdef _WIN32
	int re = recv(fd, buf, 1, 0);
#else
	//linux中是管道，不能用recv
	int re = read(fd, buf, 1);
#endif
	if (re <= 0)
		return;
	std::cout << id << "thread" << buf << std::endl;

	XTask* task = nullptr;
	tasks_mutex.lock();
	if (tasks.empty()) {
		tasks_mutex.unlock();
		return;
	}
	task = tasks.front();
	tasks.pop_front();
	tasks_mutex.unlock();
	task->Init();
}

void  XThread::Activate(){

#ifdef _WIN32
	int re = send(this->notify_send_fd, "c", 1,0);
#else
	int re = write(this->notify_send_fd, "c", 1);
#endif
	if (re <= 0) {
		std::cerr << "XThread::Active()failed!" << std::endl;
	}
}

void  XThread::AddTask(XTask* t) {
	if (!t)return;
	t->base = this->base;
	tasks_mutex.lock();
	tasks.push_back(t);
	tasks_mutex.unlock();
}

XThread::XThread() {

}

XThread::~XThread() {

}