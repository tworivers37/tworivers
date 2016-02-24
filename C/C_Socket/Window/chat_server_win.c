#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<process.h>

#define BUF_SIZE 100
#define MAX_CLIENT 256

unsigned WINAPI HandleClient(void*arg);
void SendMsg(char*msg,int len);
void ErrorHandling(char*msg);

int client_cnt=0;
SOCKET client_socks[MAX_CLIENT];
HANDLE mutex;

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock,client_sock;
	SOCKADDR_IN serv_addr,client_addr;
	int client_addr_size;
	HANDLE thread;
	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	mutex=CreateMutex(NULL,FALSE,NULL);
	serv_sock=socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR)
		ErrorHandling("bind error");

	if(listen(serv_sock,5)==SOCKET_ERROR)
		ErrorHandling("listen error");

	while(1){
		client_addr_size=sizeof(client_addr);
		client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&client_addr_size);

		WaitForSingleObject(mutex,INFINITE);
		client_socks[client_cnt++]=client_sock;
		ReleaseMutex(mutex);

		thread=(HANDLE)_beginthreadex(NULL,0,HandleClient,(void*)&client_sock,0,NULL);
		printf("Connected client IP : %s \n",inet_ntoa(client_addr.sin_addr));

	}
	closesocket(serv_sock);
	WSACleanup();
}

unsigned WINAPI HandleClient(void*arg){
	SOCKET client_sock=*((SOCKET*)arg);
	int strLen=0,i;
	char msg[BUF_SIZE];

	while((strLen=recv(client_sock,msg,sizeof(msg),0))!=0) SendMsg(msg,strLen);

	WaitForSingleObject(mutex,INFINITE);
	for(i=0;i<client_cnt;i++){
		if(client_sock==client_socks[i]){
			while(i++<client_cnt-1) client_socks[i]=client_socks[i+1];
			break;
		}
	}
	client_cnt--;
	ReleaseMutex(mutex);
	closesocket(client_sock);
	return 0;
}

void SendMsg(char*msg,int len){
	int i;
	WaitForSingleObject(mutex,INFINITE);
	for(i=0;i<client_cnt;i++) send(client_socks[i],msg,len,0);
	ReleaseMutex(mutex);
}

void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}