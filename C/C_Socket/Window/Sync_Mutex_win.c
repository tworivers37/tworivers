#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void*arg);
unsigned WINAPI threadDec(void*arg);

long long num=0;
HANDLE mutex;

void main(int argc,char**argv){
	HANDLE handles[NUM_THREAD];
	int i;

	mutex=CreateMutex(NULL,FALSE,NULL);//TRUE : non-signaled(사용중) , FALSE : signaled(아무나 사용가능)
	for(i=0;i<NUM_THREAD;i++){
		if(i%2) handles[i]=(HANDLE)_beginthreadex(NULL,0,threadInc,NULL,0,NULL);
		else handles[i]=(HANDLE)_beginthreadex(NULL,0,threadDec,NULL,0,NULL);
	}
	WaitForMultipleObjects(NUM_THREAD,handles,TRUE,INFINITE);
	CloseHandle(mutex);
	printf("result : %lld\n",num);
}
unsigned WINAPI threadInc(void*arg){
	int i;
	WaitForSingleObject(mutex,INFINITE);
	for(i=0;i<50000;i++) num+=1;
	ReleaseMutex(mutex);
	return 0;
}
unsigned WINAPI threadDec(void*arg){
	int i;
	WaitForSingleObject(mutex,INFINITE);
	for(i=0;i<50000;i++) num-=1;
	ReleaseMutex(mutex);
	return 0;
}