#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>


#define NITERS 10000000

unsigned int cnt =0;
void* count(void*);
pthread_mutex_t mutex;


int main(){
	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&tid1,NULL,count,NULL);
	pthread_create(&tid2,NULL,count,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	
	pthread_mutex_destroy(&mutex);	


	if(cnt!=(unsigned)NITERS*2)
		printf("OK cnt=%d\n",cnt);
	else 
		printf("NO cnt=%d\n",cnt);
		

	return 0;
}

void* count(void* data){
	int i;
	for(i=0;i<NITERS;++i){
		pthread_mutex_lock(&mutex);
		cnt++;
		pthread_mutex_unlock(&mutex);
	}
}
