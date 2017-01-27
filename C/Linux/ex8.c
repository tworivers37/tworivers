#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

void*thread(void*);

int main(){
	pthread_t threads[5];
	int rc,t;
	for(t=0;t<5;++t){
		printf("In main : creating thrad %d\n",t);
		rc=pthread_create(&threads[t],NULL,thread,(void*)&t);
		sleep(1);
		if(rc){
			printf("thread creation error\n");
			exit(1);
		}

	}
	pthread_exit(NULL);
	return 0;
}

void * thread(void*data){
	int id=*(int*)data;
	sleep(id);
	printf("Hello thread : %d\n",id);
	pthread_exit(NULL);
}


