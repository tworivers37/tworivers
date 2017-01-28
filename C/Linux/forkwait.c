#include<stdio.h>
#include<wait.h>

int main(){
	int pid,child,status;
	
	printf("%d parent process start \n",getpid());
	pid=fork();
	if(pid==0){
		printf("%d child process start \n",getpid());
		exit(1);
	}
	
	child=wait(&status);
	printf("%d child process exit %d\n",getpid(),child);
	printf("exit code %d \n",status);

	return 0;
}
