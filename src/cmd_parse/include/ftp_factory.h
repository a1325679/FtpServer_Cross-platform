#ifndef _FTP_FACTORY_H
#define _FTP_FACTORY_H
#include "xtask.h"
class FtpFactory
{
public:
	static FtpFactory* Get()
	{
		static FtpFactory f;
		return &f;
	}
	XTask* CreateTask();
private:
	FtpFactory();
};
#endif