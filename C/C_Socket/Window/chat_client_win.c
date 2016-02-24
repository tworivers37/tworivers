#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void*arg);
unsigned WINAPI RecvMsg(void*arg);
void ErrorHandling(char*message);

char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serv_addr;
	HANDLE send_thread,recv_thread;

	if(argc!=4){
		printf("Usage : %s <IP> <PORT> <NAME> \n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	sprintf(name,"[%s]",argv[3]);
	sock=socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR) ErrorHandling("connect error");

	send_thread=(HANDLE)_beginthreadex(NULL,0,SendMsg,(void*)&sock,0,NULL);
	recv_thread=(HANDLE)_beginthreadex(NULL,0,RecvMsg,(void*)&sock,0,NULL);

	WaitForSingleObject(send_thread,INFINITE);
	WaitForSingleObject(recv_thread,INFINITE);

	closesocket(sock);
	WSACleanup();
}

unsigned WINAPI SendMsg(void*arg){
	SOCKET sock=*((SOCKET*)arg);
	char nameMsg[NAME_SIZE+BUF_SIZE];

	while(1){
		fgets(msg,BUF_SIZE,stdin);

		if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n")){
			closesocket(sock);
			exit(0);
		}
		sprintf(nameMsg,"%s %s",name,msg);
		send(sock,nameMsg,strlen(nameMsg),0);

	}
	return 0;
}

unsigned WINAPI RecvMsg(void*arg){
	int sock=*((SOCKET*)arg);
	char nameMsg[NAME_SIZE+BUF_SIZE];
	int strLen;

	while(1){
		strLen=recv(sock,nameMsg,NAME_SIZE+BUF_SIZE-1,0);
		if(strLen==-1) return -1;
		nameMsg[strLen]=0;
		fputs(nameMsg,stdout);
	}
	return 0;
}

void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}