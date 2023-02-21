#include "ftp_rmd.h"
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpRmd::Parse(std::string type, std::string msg)
{
	int head = msg.find(" ");
	int back = msg.find("\r\n");
	std::string name = msg.substr(head + 1, back - head - 1);
	int ret = rmdir(name.c_str());
	if (ret == -1)
	{
		ResCMD("501 " + msg + " delete failed." + "\r\n");
		return;
	}
	ResCMD("257 " + msg + " success delete." + "\r\n");
	return;
}