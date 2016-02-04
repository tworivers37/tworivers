#include<stdio.h>
#include<unistd.h>

int main(int argc,char **argv){
	pid_t pid=fork();
	if(pid==0)// child
		puts("child");
	else{
		printf("Child PID : %d\n",pid);
		sleep(30);
	}
	if(pid==0) puts("End Child");
	else puts("End Parent");
	return 0;
}		
