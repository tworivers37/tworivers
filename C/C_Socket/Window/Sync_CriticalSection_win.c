#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI ThreadInc(void*arg);
unsigned WINAPI ThreadDec(void*arg);

long long num=0;
CRITICAL_SECTION cs;

void main(int argc,char**argv){
	HANDLE handles[NUM_THREAD];
	int i;

	//유저모드에서의 동기화
	//CRITICAL SECTION 을 이용한 동기화.
	InitializeCriticalSection(&cs);
	for(i=0;i<NUM_THREAD;i++){
		if(i%2) handles[i]=(HANDLE)_beginthreadex(NULL,0,ThreadInc,NULL,0,NULL);
		else handles[i]=(HANDLE)_beginthreadex(NULL,0,ThreadDec,NULL,0,NULL);
	}
	WaitForMultipleObjects(NUM_THREAD,handles,TRUE,INFINITE);
	DeleteCriticalSection(&cs);
	printf("result : %lld\n",num);

}

unsigned WINAPI ThreadInc(void*arg){
	int i;
	EnterCriticalSection(&cs);
	for(i=0;i<50000;i++) num+=1;
	LeaveCriticalSection(&cs);
	return 0;
}
unsigned WINAPI ThreadDec(void*arg){
	int i;
	EnterCriticalSection(&cs);
	for(i=0;i<50000;i++) num-=1;
	LeaveCriticalSection(&cs);
	return 0;
}