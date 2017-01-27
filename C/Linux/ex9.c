#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void*thread(void*data){
	int num=*(int*)data;
	printf("num : %d\n",num);
	sleep(1);
	return (void*) (num*num);
}

int main(){
	pthread_t th;
	int tid;
	int status;
	int a=100;
	
	tid=pthread_create(&th,NULL,thread,(void*)&a);
	pthread_join(th,(void*)&status);
	printf("thread join : %d\n",status);	

	return 0;
}


