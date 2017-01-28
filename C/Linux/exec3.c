#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char**argv){
	int child,pid,status;
	pid=fork();
	if(pid==0){
		execvp(argv[1],&argv[1]);
		fprintf(stderr,"%s failed \n",argv[1]);
		
	}
	else{
		child=wait(&status);
		printf("%d child process %d finished\n",getpid(),pid);
		printf("exit code %d \n",status>>8);
	}

	return 0;
}
