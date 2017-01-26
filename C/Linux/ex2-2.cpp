#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>

int main(){
	int fd;
	mode_t oldmask;
	
	oldmask=umask(033);//000 011 011 -> 111 100 100

	//111 111 111
	//111 100 100
	//111 100 100 rwx r-- r--
	fd=open("fd.txt",O_CREAT,0777);
	
	close(fd);
	
	

	return 0;
}
