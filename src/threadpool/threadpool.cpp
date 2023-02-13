#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <atomic>

#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <thread>
#include <future>

#include "threadpool.h"
using namespace std;
int Thread::generateId_ = 0;

ThreadPool::ThreadPool()
		: initThreadSize_(0), taskSize_(0), idleThreadSize_(0), curThreadSize_(0), taskQueMaxThreshHold_(TASK_MAX_THRESHHOLD), threadSizeThreshHold_(THREAD_MAX_THRESHHOLD)
{
}
ThreadPool::~ThreadPool()
{
	isPoolRunning_ = false;

	// 等待线程池里面所有的线程返回  有两种状态：阻塞 & 正在执行任务中
	std::unique_lock<std::mutex> lock(taskQueMtx_);
	notEmpty_.notify_all();
	exitCond_.wait(lock, [&]() -> bool
								 { return threads_.size() == 0; });
}
void ThreadPool::setMode(PoolMode mode)
{
	// 设置线程池的工作模式
	if (checkRunningState())
		return;
	poolMode_ = mode;
}

// 设置task任务队列上线阈值
void ThreadPool::setTaskQueMaxThreshHold(int threshhold)
{
	if (checkRunningState())
		return;
	taskQueMaxThreshHold_ = threshhold;
}

// 设置线程池cached模式下线程阈值
void ThreadPool::setThreadSizeThreshHold(int threshhold)
{
	if (checkRunningState())
		return;
	if (poolMode_ == PoolMode::MODE_CACHED)
	{
		threadSizeThreshHold_ = threshhold;
	}
}

void ThreadPool::start(int initThreadSize)
{
	// 设置线程池的运行状态
	isPoolRunning_ = true;
	// 记录初始线程个数
	initThreadSize_ = initThreadSize;
	curThreadSize_ = initThreadSize;

	// 创建线程对象
	for (int i = 0; i < initThreadSize_; i++)
	{
		// 创建thread线程对象的时候，把线程函数给到thread线程对象
		auto ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
		int threadId = ptr->getId();
		threads_.emplace(threadId, std::move(ptr));
		// threads_.emplace_back(std::move(ptr));
	}

	// 启动所有线程  std::vector<Thread*> threads_;
	for (int i = 0; i < initThreadSize_; i++)
	{
		threads_[i]->start(); // 需要去执行一个线程函数
		idleThreadSize_++;		// 记录初始空闲线程的数量
	}
	this_thread::sleep_for(1s);
	// usleep(500 * 100);
}

// 定义线程函数
void ThreadPool::threadFunc(int threadid)
{
	auto lastTime = std::chrono::high_resolution_clock().now();

	// 所有任务必须执行完成，线程池才可以回收所有线程资源
	for (;;)
	{

		Task task;
		{
			// 先获取锁
			std::unique_lock<std::mutex> lock(taskQueMtx_);
			std::cout << "tid:" << std::this_thread::get_id()
								<< "尝试获取任务..." << std::endl;

			// cached模式下，有可能已经创建了很多的线程，但是空闲时间超过60s，应该把多余的线程
			// 结束回收掉（超过initThreadSize_数量的线程要进行回收）
			// 当前时间 - 上一次线程执行的时间 > 60s
			while (taskQue_.size() == 0)
			{
				// 线程池要结束，回收线程资源
				if (!isPoolRunning_)
				{
					threads_.erase(threadid); // std::this_thread::getid()
					std::cout << "threadid:" << std::this_thread::get_id() << " exit!"
										<< std::endl;
					exitCond_.notify_all();
					return; // 线程函数结束，线程结束
				}

				if (poolMode_ == PoolMode::MODE_CACHED)
				{
					// 条件变量，超时返回了
					if (std::cv_status::timeout ==
							notEmpty_.wait_for(lock, std::chrono::seconds(1)))
					{
						auto now = std::chrono::high_resolution_clock().now();
						auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
						if (dur.count() >= THREAD_MAX_IDLE_TIME && curThreadSize_ > initThreadSize_)
						{
							threads_.erase(threadid); // std::this_thread::getid()
							curThreadSize_--;
							idleThreadSize_--;

							std::cout << "threadid:" << std::this_thread::get_id() << " exit!"
												<< std::endl;
							return;
						}
					}
				}
				else
				{
					// 等待notEmpty条件
					notEmpty_.wait(lock);
				}
			}

			idleThreadSize_--;

			std::cout << "tid:" << std::this_thread::get_id()
								<< "获取任务成功..." << std::endl;

			// 从任务队列种取一个任务出来
			task = taskQue_.front();
			taskQue_.pop();
			taskSize_--;

			// 如果依然有剩余任务，继续通知其它得线程执行任务
			if (taskQue_.size() > 0)
			{
				notEmpty_.notify_all();
			}

			// 取出一个任务，进行通知，通知可以继续提交生产任务
			notFull_.notify_all();
		} // 就应该把锁释放掉

		// 当前线程负责执行这个任务
		if (task != nullptr)
		{
			// 执行function<void()>
			task();
		}

		idleThreadSize_++;
		lastTime = std::chrono::high_resolution_clock().now(); // 更新线程执行完任务的时间
	}
}