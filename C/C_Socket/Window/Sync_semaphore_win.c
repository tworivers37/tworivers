#include<stdio.h>
#include<Windows.h>
#include<process.h>

unsigned WINAPI Read(void*arg);
unsigned WINAPI Accu(void*arg);

static HANDLE semOne;
static HANDLE semTwo;
static int num;

void main(int argc,char**argv){
	HANDLE thread1,thread2;

	//세마포어가 0이면 non-signaled
	//세마포어가 0보다 크면 signaled
	semOne=CreateSemaphore(NULL,0,1,NULL); //초기값 : 0 , 최대값 : 1
	semTwo=CreateSemaphore(NULL,1,1,NULL); //초기값 : 1 , 최대값 : 1

	thread1=(HANDLE)_beginthreadex(NULL,0,Read,NULL,0,NULL);
	thread2=(HANDLE)_beginthreadex(NULL,0,Accu,NULL,0,NULL);

	WaitForSingleObject(thread1,INFINITE);
	WaitForSingleObject(thread2,INFINITE);

	CloseHandle(thread1);
	CloseHandle(thread2);
}

unsigned WINAPI Read(void*arg){
	int i;
	for(i=0;i<5;i++){
		fputs("Input num : ",stdout);
		WaitForSingleObject(semTwo,INFINITE);
		scanf("%d",&num);
		ReleaseSemaphore(semOne,1,NULL);
	}
	return 0;
}

unsigned WINAPI Accu(void*arg){
	int i,sum=0;
	for(i=0;i<5;i++){
		WaitForSingleObject(semOne,INFINITE);
		sum+=num;
		ReleaseSemaphore(semTwo,1,NULL);
	}
	printf("result : %d\n",sum);
	return 0;
}