#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

using namespace std;

int main(){
	int fd,fd2;
	ssize_t nRead;
	off_t newPos;

	char buffer[255];
	char content[]="Hello\n";

	fd=open("data",O_RDWR);
		
	nRead=read(fd,buffer,255);
	write(1,buffer,nRead);
	
	write(fd,content,7);

	newPos=lseek(fd,(off_t)5,SEEK_SET);
	nRead=read(fd,buffer,255);
	write(1,buffer,nRead);
	
	close(fd);

	fd2=creat("data2",0644);	

	close(fd2);
	unlink("data2");

	return 0;
}
