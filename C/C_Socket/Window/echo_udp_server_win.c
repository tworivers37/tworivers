#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 30

void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock; //udp 이므로 client 소켓은 필요x
	char message[BUF_SIZE];
	int strLen;
	int client_addr_size;
	SOCKADDR_IN serv_addr,client_addr;

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	serv_sock=socket(PF_INET,SOCK_DGRAM,0);
	if(serv_sock==INVALID_SOCKET) ErrorHandling("UDP socket error");

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR)
		ErrorHandling("bind error");

	while(1){
		client_addr_size=sizeof(client_addr);
		strLen=recvfrom(serv_sock,message,BUF_SIZE,0,(SOCKADDR*)&client_addr,&client_addr_size);
		sendto(serv_sock,message,strLen,0,(SOCKADDR*)&client_addr,sizeof(client_addr));
	}
	closesocket(serv_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}