#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

int main(){
	pid_t pid;
	if((pid=fork())>0){
		sleep(1);
		exit(1);
	}
	else if(pid==0){
		cout<<"old session id : "<<getsid(0)<<endl;
		cout<<"new session id : "<<setsid()<<endl;
		cout<<"new session id : "<<getsid(0)<<endl;
		sleep(100);
	}
	return 0;
}
