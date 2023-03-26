#include "ftp_factory.h"
#include "ftp_server_cmd.h"
#include "ftp_user.h"
#include "ftp_pwd.h"
#include "ftp_port.h"
#include "ftp_list.h"
#include "ftp_cudp.h"
#include "ftp_cwd.h"
#include "ftp_mkd.h"
#include "ftp_rmd.h"
#include "ftp_retr.h"
#include "ftp_stor.h"
#include "ftp_dele.h"
#include "ftp_rnfr.h"
#include "ftp_rnto.h"
XTask *FtpFactory::CreateTask()
{
  FtpServerCMD *x = new FtpServerCMD();

  // 注册ftp消息处理对象
  x->Reg("USER", new FtpUser());
  x->Reg("PORT", new FtpPort());
  x->Reg("PWD", new FtpPWD());
  x->Reg("LIST", new FtpList());
  x->Reg("CWD", new FtpCwd());
  x->Reg("CDUP", new FtpCudp());
  x->Reg("MKD", new FtpMkd());
  x->Reg("RMD", new FtpRmd());
  x->Reg("RETR", new FtpRetr());
  x->Reg("STOR", new FtpStor());
  x->Reg("DELE", new FtpDele());
  x->Reg("RNFR", new FtpRnfr());
  x->Reg("RNTO", new FtpRnto());
  return x;
}

FtpFactory::FtpFactory()
{
}