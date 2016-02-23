#include<stdio.h>
#include<Windows.h>
#include<process.h>
unsigned WINAPI ThreadFunc(void*);

void main(int argc,char**argv){
	HANDLE thread;
	unsigned threadID;
	int param=5;

	thread=(HANDLE)_beginthreadex(NULL,0,ThreadFunc,(void*)&param,0,&threadID); //thread 생성
	if(thread==0){
		puts("_beginthreadex error");
		exit(1);
	}
	Sleep(3000); //main 함수 종료로 인해 thread 까지 종료
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