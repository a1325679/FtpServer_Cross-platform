#include "ftp_port.h"
#include "macor.h"
#include "log.h"
#include <vector>
#include <iostream>
using namespace std;

void FtpPort::Parse(std::string type, std::string msg)
{
  std::string temp = msg;
  if (temp.find("\r\n") != std::string::npos)
  {
    temp.pop_back();
    temp.pop_back();
  }
  log(NOTICE, "%s:%d %s:%d -> 解析命令%s,命令内容为%s", __FILE__, __LINE__, ipaddr.c_str(), portFrom, type.c_str(),temp.c_str());

  vector<string> vals;
  string tmp = "";
  for (int i = 5; i < msg.size(); i++)
  {
    if (msg[i] == ',' || msg[i] == '\r')
    {
      vals.push_back(tmp);
      tmp = "";
      continue;
    }
    tmp += msg[i];
  }
  if (vals.size() != 6)
  {
    // PORT格式有误
    ResCMD("501 Syntax error in parameters or arguments.");
    return;
  }
  ip = vals[0] + "." + vals[1] + "." + vals[2] + "." + vals[3];
  port = atoi(vals[4].c_str()) * 256 + atoi(vals[5].c_str());
  //cout << "PORT ip is " << ip << endl;
  //cout << "PORT port is " << port << endl;
  ResCMD("200 PORT command successful.\r\n");
}