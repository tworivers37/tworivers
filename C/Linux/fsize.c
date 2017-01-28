#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char**argv){
	char buffer[256];
	int fd;
	ssize_t nread;
	long total=0;

	if((fd=open(argv[1],O_RDONLY))==-1){
		perror(argv[1]);
	}
	while((nread=read(fd,buffer,256))>0)
		total+=nread;
	close(fd);
	printf("%s file size : %ld\n",argv[1],total);
	return 0;
}
