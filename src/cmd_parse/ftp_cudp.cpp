#include "ftp_cudp.h"
#include<iostream>
#include <string>
using namespace std;
void FtpCudp::Parse(std::string type,std::string msg)
{
	string path = cmdTask->curDir;
	if(path[path.size()-1]=='/')
	{
		path = path.substr(0, path.size() - 1);
	}
	int pos = path.rfind("/");
	path = path.substr(0, pos);
	cmdTask->curDir = path;
	ResCMD("250 Directory success changed. \r\n");
}