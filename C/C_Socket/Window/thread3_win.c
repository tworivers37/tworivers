#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define NUM_THREAD 50
unsigned WINAPI threadInc(void*arg);
unsigned WINAPI threadDec(void*arg);
long long num=0;

void main(int argc,char**argv){
	HANDLE handles[NUM_THREAD];
	int i;
	printf("sizeof long long : %d \n",sizeof(long long));
	
	//쓰레드 동기화 필요
	for(i=0;i<NUM_THREAD;i++){
		if(i%2)
			handles[i]=(HANDLE)_beginthreadex(NULL,0,threadInc,NULL,0,NULL);
		else
			handles[i]=(HANDLE)_beginthreadex(NULL,0,threadDec,NULL,0,NULL);
	}
	WaitForMultipleObjects(NUM_THREAD,handles,TRUE,INFINITE);	//TRUE : 배열의 모든 항목들이 signaled 되어야 반환.
																//FALSE : 배열의 항목 중 하나라도 signaled 되면 반환.
	printf("result : %lld\n",num);

}

unsigned WINAPI threadInc(void*arg){
	int i;
	for(i=0;i<50000;i++) num+=1;
	return 0;
}

unsigned WINAPI threadDec(void*arg){
	int i;
	for(i=0;i<50000;i++) num-=i;
	return 0;
}