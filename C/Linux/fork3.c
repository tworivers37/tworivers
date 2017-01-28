#include<stdio.h>
#include<stdlib.h>

int main(){
	int pid1,pid2;

	pid1=fork();
	if(pid1==0){
		printf("child1 pid : %d \n",getpid());
		exit(0);
	}
	pid2=fork();
	if(pid2==0){
		printf("child2 pid : %d \n",getpid());
		exit(0);
	}
		
	return 0;
}
