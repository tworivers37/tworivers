#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

#define BUF_SIZE 30

void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN sock_addr;
	if(argc!=3){
		printf("Usage : %s <IP> <PORT>\n",argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family=AF_INET;
	sock_addr.sin_port=htons(atoi(argv[2]));
	sock_addr.sin_addr.s_addr=inet_addr(argv[1]);

	if(connect(sock,(SOCKADDR*)&sock_addr,sizeof(sock_addr))==SOCKET_ERROR)
		ErrorHandling("connect error");

	send(sock,"123",3,0);
	send(sock,"4",1,MSG_OOB);
	send(sock,"567",3,0);
	send(sock,"890",3,MSG_OOB);

	closesocket(sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}