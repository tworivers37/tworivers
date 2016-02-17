#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 1024

void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock,client_sock;
	char message[BUF_SIZE];
	int strLen,i;

	SOCKADDR_IN serv_addr,client_addr;
	int client_addr_size;

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==INVALID_SOCKET) ErrorHandling("socket error");

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR) ErrorHandling("bind error");

	if(listen(serv_sock,5)==SOCKET_ERROR) ErrorHandling("listen error");

	client_addr_size=sizeof(client_addr);
	for(i=0;i<5;i++){
		client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&client_addr_size);
		if(client_sock==-1) ErrorHandling("accept error");
		else printf("Connected client %d \n",i+1);
		while((strLen=recv(client_sock,message,BUF_SIZE,0))!=0)
			send(client_sock,message,strLen,0);
		closesocket(client_sock);
	}
	closesocket(serv_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}