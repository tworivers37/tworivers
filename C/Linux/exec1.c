#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	printf("parent process start \n");
	if(fork()==0){
		execl("/bin/echo","echo","hello",NULL);
		fprintf(stderr,"failed");
		exit(1);
	}
	sleep(1);
	printf("parent process exit\n");
	return 0;
}
