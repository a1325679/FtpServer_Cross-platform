#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include<vector>
class XTask;
class XThread;
class XThreadPool
{
public:
	static XThreadPool* Get() {
		static XThreadPool pool;
		return &pool;
	}
	void Init(int threadCount);

	void Dispatch(XTask* task);
private:
	unsigned int threadCount = 0;
	unsigned int lastThread = -1;
	std::vector<XThread*> threads;
	XThreadPool(){
	}
};
#endif
