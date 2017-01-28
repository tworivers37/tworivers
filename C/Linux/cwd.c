#include<stdio.h>
#include<unistd.h>

#define BUF_SIZE 256

void printcwd(){
	char buffer[BUF_SIZE];
	if(getcwd(buffer,BUF_SIZE)==NULL)
		exit(1);
	printf("%s \n",buffer);
}

int main(){
	printcwd();
	chdir("/home/bw/workspace/");
	printcwd();
	chdir("..");
	printcwd();
	return 0;
}
