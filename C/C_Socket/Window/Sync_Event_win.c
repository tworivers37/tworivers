#include<stdio.h>
#include<Windows.h>
#include<process.h>

#define STR_LEN 100

unsigned WINAPI NumberOfA(void*arg);
unsigned WINAPI NumberOfOthers(void*arg);

static char str[STR_LEN];
static HANDLE event;

void main(int argc,char**argv){
	HANDLE thread1,thread2;
	//Event 오브젝트 기반 동기화에서는 auto-reset 모드와 
	//manual-reset 모드 중 선택할 수 있음.
	//두 번째 인자 TRUE(manual-reset) , FALSE(auto-reset)
	//세 번째 인자 TRUE(signaled) , FALSE(non-signaled)
	event=CreateEvent(NULL,TRUE,FALSE,NULL); //manual-reset & non-signaled

	thread1=(HANDLE)_beginthreadex(NULL,0,NumberOfA,NULL,0,NULL);
	thread2=(HANDLE)_beginthreadex(NULL,0,NumberOfOthers,NULL,0,NULL);

	fputs("Input string : ",stdout);
	fgets(str,STR_LEN,stdin);
	SetEvent(event);//signaled

	WaitForSingleObject(thread1,INFINITE);
	WaitForSingleObject(thread2,INFINITE);

	ResetEvent(event);//non-signaled
	CloseHandle(event);
}

unsigned WINAPI NumberOfA(void*arg){
	int i,cnt=0;
	WaitForSingleObject(event,INFINITE); // 함수 호출 후 에도 계속 signaled 
	for(i=0;str[i]!=0;i++) if(str[i]=='A') cnt++;
	printf("Num of A : %d \n",cnt);
	return 0;
}

unsigned WINAPI NumberOfOthers(void*arg){
	int i,cnt=0;
	WaitForSingleObject(event,INFINITE); // 함수 호출 후 에도 계속 signaled 
	for(i=0;str[i]!=0;i++) if(str[i]!='A') cnt++;
	printf("Num of Others : %d \n",cnt-1);
	return 0;
}