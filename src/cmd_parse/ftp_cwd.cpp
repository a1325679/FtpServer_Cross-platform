#include "ftp_cwd.h"
#include<iostream>
#include<string>
using namespace std;
void FtpCwd::Parse(std::string type, std::string msg) {
	//取出命令中的路径
	//CWD test\r\n
	int pos = msg.rfind(" ") + 1;
	//去掉结尾的\r\n
	string path = msg.substr(pos, msg.size() - pos - 2);
	if (path[0] == '/') //局对路径
	{
		cmdTask->curDir = path;
	}
	else
	{
		if (cmdTask->curDir[cmdTask->curDir.size() - 1] != '/')
			cmdTask->curDir += "/";
		cmdTask->curDir += path + "/";
	}
	//  /test/
	ResCMD("250 Directory succes chanaged.\r\n");

	//cmdTask->curDir += 
}