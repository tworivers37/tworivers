#include<stdio.h>
#include<pthread.h>

#define NUM_THREAD 100

void* thread_inc(void *arg);
void* thread_dec(void *arg);

long long num=0;
pthread_mutex_t mutex;

int main(int argc,char **argv){
	pthread_t thread_id[NUM_THREAD];
	int i;

	pthread_mutex_init(&mutex,NULL);
	//pthread_mutex_init 의 두번째 인자가 NULL 일 때
	//pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
	//로 초기화 가능함. 그러나 추천은 하지 않음.
	//오류 발생 확인이 어렵기 때문.
	for(i=0;i<NUM_THREAD;i++){
		if(i%2) pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);
		else pthread_create(&(thread_id[i]),NULL,thread_dec,NULL);
	}
	for(i=0;i<NUM_THREAD;i++) pthread_join(thread_id[i],NULL);

	printf("result : %lld \n",num);
	pthread_mutex_destroy(&mutex);
	return 0;
}

void* thread_inc(void*arg){
	int i;
	//i가 50000가 될 때 까지 다른 스레드 접근 안됨.
	printf("thread_inc(%d)\n",num);
	pthread_mutex_lock(&mutex);
	for(i=0;i<5000;i++) num+=1;
	pthread_mutex_unlock(&mutex);
	return NULL;
}
void* thread_dec(void*arg){
	int i;
	//pthread_mutex_lock 과 pthread_mutex_unlock 함수 반복적 호출.
	printf("thread_dec(%d)\n",num);
	for(i=0;i<5000;i++){
		pthread_mutex_lock(&mutex);
		num-=1;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
