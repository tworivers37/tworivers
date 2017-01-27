#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>

using namespace std;

int main(){
	pid_t pid;
	int status;
	pid=fork();
	putenv("APPLE=RED");
	if(pid>0){
		cout<<"parent PID : "<<getpid()<<endl;
		cout<<"parent PPID : "<<getppid()<<endl;
		cout<<"parent GID : "<<getpgrp()<<endl;
		cout<<"parent SID : "<<getsid(0)<<endl;
		waitpid(pid,&status,0);
		cout<<"parent status is "<<status<<endl;
		unsetenv("APPLE");
	}
	else if(pid==0){
		cout<<"child PID : "<<getpid()<<endl;
		cout<<"child PPID : "<<getppid()<<endl;
		cout<<"child GID : "<<getpgrp()<<endl;
		cout<<"child SID : "<<getsid(0)<<endl;
		sleep(1);
		cout<<"child APPLE = "<<getenv("APPLE")<<endl;
		exit(1);
	}
	else cout<<"fail to fork"<<endl;
	return 0;
}
