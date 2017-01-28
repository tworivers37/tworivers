#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	printf("parent process start %d\n",getpid());
	if(fork()==0){
		printf("child : %d \n",getpid());
		execl("/bin/echo","echo","hello",NULL);
		fprintf(stderr,"first fail");
		exit(1);
	}
	if(fork()==0){
		printf("child : %d \n",getpid());
		execl("/bin/date","date",NULL);
		fprintf(stderr,"second fail");
		exit(2);
	}
	if(fork()==0){
		printf("child : %d \n",getpid());
		execl("/bin/ls","ls","-l","data",NULL);
		fprintf(stderr,"third fail");
		exit(3);
	}
	printf("parent process exit %d\n",getpid());
	return 0;
}
