#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>


using namespace std;

void clean_up_action();

int main(){
	pid_t pid;
	int i;
	char* argv[]={"ls","-ail","/home/bw/workspace/ex4",NULL};
	for(i=0;i<3;++i){
		cout<<"before fork "<<i<<endl;
		sleep(1);
	}
	pid=fork();

	if(pid>0){
		for(;i<7;++i){
			cout<<"parent "<<i<<endl;
			sleep(1);	
		}
	}
	else if(pid==0){
		for(;i<5;++i){
			cout<<"child "<<i<<endl;
			sleep(1);
			execv("/bin/ls",argv);
		}
	}
	else cout<<"fail to fork child process"<<endl;	
	
	exit(0);
	return 0;
}
void clean_up_action(){
	cout<<"clean up action"<<endl;
}
