#include "ftp_user.h"
#include <iostream>
using namespace std;
//解析协议
void FtpUser::Parse(std::string type, std::string msg)
{
	cout << "XFtpUSER::Parse " << type << " " << msg << endl;
	ResCMD("230 Login successful.\r\n");
}

FtpUser::FtpUser()
{
}


FtpUser::~FtpUser()
{
}
