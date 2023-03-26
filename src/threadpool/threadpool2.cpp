#include "threadpool2.h"
#include"threads.h"
#include<thread>
#include<iostream>
using namespace std;
void XThreadPool::Init(int threadCount) {
	this->threadCount = threadCount;
	this->lastThread = -1;
	for (int i = 0; i < threadCount; i++) {
		XThread* t = new XThread();
		t->id = i + 1;
		t->Start();
		threads.push_back(t);
		this_thread::sleep_for(10ms);
	}
}

void XThreadPool::Dispatch(XTask* task) {
	//轮询
	if (!task)return;
	int tid = (lastThread + 1) % threadCount;
	lastThread = tid;
	XThread* t = threads[tid];
	t->AddTask(task);

	//激活线程
	t->Activate();
}