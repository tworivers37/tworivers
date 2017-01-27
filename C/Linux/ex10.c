#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>


void* work(void* data){
	int i;
	double result=0.0;
	for(i=0;i<10000;++i) result+=(double)random();
	printf("result = %d\n",result);
	pthread_exit((void*)0);
}

int main(){
	pthread_t thread[3];
	pthread_attr_t attr;
	int rc,t;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	for(t=0;t<3;++t){
		printf("Creating thread %d\n",t);
		rc=pthread_create(&thread[t],&attr,work,NULL);
	}
	pthread_attr_destroy(&attr);
	for(t=0;t<3;++t){
		rc=pthread_join(thread[t],&status);
		printf("Completed join with thread %d status %ld\n",t,(long)status);
	}
	pthread_exit(NULL);

	return 0;
}
