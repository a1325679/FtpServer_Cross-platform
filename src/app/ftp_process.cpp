#include "func.h"
#include "macor.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int ftp_daemon() {
  switch (fork())
	{
    case -1:
      log_(EMERG,"ftp_daemon()中fork()失败!");
      return -1;
    case 0:
      break;
    default:
      return 1;
	}
	pid_t ngx_pid = getpid();
	if (setsid() == -1)
	{
		return -1;
	}

	//(3)设置为0，不要让它来限制文件权限，以免引起混乱
	umask(0);

	//(4)打开黑洞设备，以读写方式打开
	int fd = open("/dev/null", O_RDWR);
	if (fd == -1)
	{
    log_(EMERG, "ftp_daemon()中open(/dev/null)失败");
    return -1;
  }
	if (dup2(fd, STDIN_FILENO) == -1) // 先关闭STDIN_FILENO[这是规矩，已经打开的描述符，动他之前，先close]，类似于指针指向null，让/dev/null成为标准输入；
	{
    log_(EMERG, "ftp_daemon()中dup2(fd, STDIN_FILENO)失败");
		return -1;
	}
	if (dup2(fd, STDOUT_FILENO) == -1) // 再关闭STDIN_FILENO，类似于指针指向null，让/dev/null成为标准输出；
	{
    log_(EMERG, "ftp_daemon()中dup2(fd, STDOUT_FILENO)失败");
		return -1;
	}
	if (fd > STDERR_FILENO) // fd应该是3，这个应该成立
	{
		if (close(fd) == -1) // 释放资源这样这个文件描述符就可以被复用；不然这个数字【文件描述符】会被一直占着；
		{
			return -1;
		}
	}
	return 0; // 子进程返回0
}