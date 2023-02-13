#include "ftp_pwd.h"
#include<iostream>
#include<string>
void FtpPWD::Parse(std::string type, std::string msg) {
	std::cout << "XFtpPWD::Parse " << type << " " << msg << std::endl;
	std::string resmsg = "";
	resmsg +="257 \"";
	resmsg += cmdTask->curDir;
	resmsg += "\" is current dir. \r\n";
	ResCMD(resmsg);
}