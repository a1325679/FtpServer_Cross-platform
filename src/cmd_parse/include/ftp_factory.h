#ifndef _FTP_FACTORY_H
#define _FTP_FACTORY_H
#include "task.h"
class FtpFactory
{
public:
	static FtpFactory* Get()
	{
		static FtpFactory f;
		return &f;
	}
	Task* CreateTask();
private:
	FtpFactory();
};
#endif