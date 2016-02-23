#include<stdio.h>
#include<Windows.h>
#include<process.h>

unsigned WINAPI ThreadFunc(void*arg);

void main(int argc,char**argv){
	HANDLE thread;
	DWORD wr;
	unsigned threadID;
	int param=5;

	thread=(HANDLE)_beginthreadex(NULL,0,ThreadFunc,(void*)&param,0,&threadID);
	if(thread==0){
		puts("_beginthreadex error");
		exit(1);
	}

	//blocking. sinaled 되면 진행.
	//signaled 로 인한 반환 : WAIT_OBJECT_0
	//timeout에 의한 반환 : WAIT_TIMEOUT
	if((wr=WaitForSingleObject(thread,INFINITE))==WAIT_FAILED){
		puts("thread wait error");
		exit(1);
	}

	printf("wait result : %s \n",(wr==WAIT_OBJECT_0)?"signaled":"time-out");
	puts("end of main");
}

unsigned WINAPI ThreadFunc(void*arg){
	int i;
	int cnt=*((int*)arg);
	for(i=0;i<cnt;i++){
		Sleep(1000);
		puts("running thread");
	}
	return 0;
}