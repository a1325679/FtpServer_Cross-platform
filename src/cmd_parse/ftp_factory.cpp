#include "ftp_factory.h"
#include "ftp_server_cmd.h"
#include "ftp_user.h"
// #include "XFtpSTOR.h"
Task* FtpFactory::CreateTask()
{
	FtpServerCMD* x = new FtpServerCMD();

	//注册ftp消息处理对象
	x->Reg("USER", new FtpUser());
	// x->Reg("PORT", new FtpPORT());
	// x->Reg("PWD", new FtpPWD());
	// x->Reg("LIST", new FtpLIST());
	// x->Reg("CWD", new FtpCWD());
	// x->Reg("CDUP", new FtpCUDP());
	// x->Reg("MKD",new FtpMKD());
	// x->Reg("RMD",new FtpRMD());
	// x->Reg("RETR", new FtpRETR());
	// x->Reg("STOR", new XFtpSTOR());

	return x;
}

FtpFactory::FtpFactory()
{
}