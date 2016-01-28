#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void childProc(int sig){
	int status;
	pid_t pid=waitpid(-1,&status,WNOHANG);
	if(WIFEXITED(status)){
		printf("Removed proc id : %d\n",pid);
		printf("Child send : %d \n",WEXITSTATUS(status));
	}
}
int main(int argc,char**argv){
	int i;
	pid_t pid;
	struct sigaction act;
	act.sa_handler=childProc;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGCHLD,&act,0);
	pid=fork();
	if(pid==0){
		puts("Child");
		sleep(10);
		return 100;
	}
	else{
		printf("Child proc id : %d \n",pid);
		pid=fork();
		if(pid==0){
			puts("Child");
			sleep(10);
			exit(300);
		}
		else{
			printf("Child proc id : %d\n",pid);
			for(i=0;i<3;i++){
				puts("wait..");
				sleep(3);
			}
		}
	}
	return 0;
}
