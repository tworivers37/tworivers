#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char**argv){

	int fd;
	if((fd=open(argv[1],O_RDWR))==-1)
		perror(argv[1]);
	else 
		printf("file %s open sucess\n",argv[1]);
	close(fd);
	exit(0);

	return 0;
}
