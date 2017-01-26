#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

int main(){
	pid_t pid1,pid2;
	int status;
	
	pid1=pid2=-1;
	cout<<"before fork : "<<pid1<<" "<<pid2<<endl;
	pid1=fork();
	cout<<"after fork : "<<pid1<<" "<<pid2<<endl;
	
	if(pid1>0){
		pid2=fork();
		cout<<"after : pid2 fork : "<<pid1<<" "<<pid2<<endl;
	}
	if(pid1>0 && pid2>0){
		waitpid(pid2,&status,0);
		cout<<"parent child2 exit : "<<status<<endl;
		waitpid(pid1,&status,0);
		cout<<"parent child1 exit : "<<status<<endl;
		cout<<"after : waitpid "<<pid1<<" "<<pid2<<endl;
	}
	else if(pid1==0 && pid2<0){
		sleep(1);
		exit(1);
		cout<<pid1<<" "<<pid2<<endl;
	}
	else if(pid1>0 && pid2==0){
		sleep(2);
		exit(2);
		cout<<pid1<<" "<<pid2<<endl;
	}
	else cout<<"fail to fork"<<endl;
	

	return 0;
}
