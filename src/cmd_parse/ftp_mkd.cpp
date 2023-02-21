#include "ftp_mkd.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
void FtpMkd::Parse(std::string type, std::string msg)
{
	int head = msg.find(" ");
	int back = msg.find("\r\n");
	std::string name = msg.substr(head + 1, back - head - 1);
	int ret = mkdir(name.c_str(), 0777);
	if (ret == -1)
	{
		ResCMD("501 " + msg + " create failed." + "\r\n");
		return;
	}
	ResCMD("257 " + msg + " success create." + "\r\n");
	return;
}