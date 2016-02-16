#include<stdio.h>
#include<pthread.h>
void* thread_test(void *arg);
void* thread_sum(void *arg);
int sum=0; 

int main(int argc,char**argv){
	pthread_t id1,id2;
	int rang1[]={1,5};
	int rang2=10;
	int i=0;

	printf("create thread 1\n");
	pthread_create(&id1,NULL,thread_sum,(void*)rang1);
	
	printf("create thread 2\n");
	pthread_create(&id2,NULL,thread_test,(void*)&rang2);
	
	//최소 thread 들이 끝날 때까진 main 은 종료 안됨.
	//pthread_join 은 해당 스레드가 종료 될 때 까지 블로킹 상태 유지.
	printf("join thread 1 : %d \n",pthread_join(id1,NULL));
	//thread 2는 작업이 이미 끝나있는 상태 일수도 있음.
	//끝난 상태라면 바로 pthread_join 함수가 바로 반환됨.
	//아니라면 블로킹 상태에서 thread 2 작업이 끝날때 까지 블로킹 상태유지.
	printf("join thread 2 : %d \n",pthread_join(id2,NULL));

	printf("main result : %d\n",sum);
	return 0;
}
void* thread_sum(void*arg){
	int start=((int*)arg)[0];
	int end=((int*)arg)[1];

	printf("thread_sum start!\n");
	while(start<=end){
		printf("sum += %d \n",start);
		sleep(1); // delay,이것으로 인해 thread 2 의 작업이 먼저 완료됨.
		sum+=start;
		start++;
	}
	printf("end thread_sum!\n");
	return NULL;
}

void* thread_test(void*arg){
	int cnt=*((int*)arg);
	int i=0;
	for(i=0;i<cnt;i++) printf("thread_test\n");
	return NULL;
}
