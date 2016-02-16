#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<pthread.h>
#include<arpa/inet.h>

#define BUF_SIZE 100
#define MAX_CLIENT 256

void* handle_client(void*arg);
void send_msg(char*message,int len);
void error_handling(char*message);

int client_cnt=0;
int client_socks[MAX_CLIENT];
pthread_mutex_t mutex;

int main(int argc,char**argv){
	int serv_sock,client_sock;
	struct sockaddr_in serv_addr,client_addr;
	int client_addr_size;
	pthread_t id;

	if(argc!=2){
		printf("Usage : %s <PORT>\n",argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutex,NULL);
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind error");	
	if(listen(serv_sock,5)==-1)
		error_handling("listen error");

	while(1){
		client_addr_size=sizeof(client_addr);
		client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&client_addr_size);
		pthread_mutex_lock(&mutex);
		client_socks[client_cnt++]=client_sock;
		pthread_mutex_unlock(&mutex);
	
		pthread_create(&id,NULL,handle_client,(void*)&client_sock);
		pthread_detach(id);
		printf("Connected client IP : %s\n",inet_ntoa(client_addr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

void* handle_client(void*arg){
	int client_sock=*((int*)arg);
	int str_len=0;
	int i;
	char msg[BUF_SIZE];

	while((str_len=read(client_sock,msg,sizeof(msg)))!=0)
		send_msg(msg,str_len);
	pthread_mutex_lock(&mutex);
	for(i=0;i<client_cnt;i++){
		if(client_sock==client_socks[i]) client_socks[i]=client_socks[i+1];
		break;
	}
	client_cnt--;
	pthread_mutex_unlock(&mutex);
	close(client_sock);
	return NULL;
}

void send_msg(char*message,int str_len){
	int i;
	pthread_mutex_lock(&mutex);
	for(i=0;i<client_cnt;i++) write(client_socks[i],message,str_len);
	pthread_mutex_unlock(&mutex);
}
void error_handling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
