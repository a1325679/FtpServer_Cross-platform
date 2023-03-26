#include<iostream>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(){

	int fd1;
	fd1=open("a.txt",O_WRONLY | O_TRUNC);
	dup2(fd1,1);
	printf("Successful file redirection");
	close(fd1);


  return 0;
}