#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#define BUF_SIZE 30
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET recv_sock;
	SOCKADDR_IN addr;
	struct ip_mreq join_addr;
	char buf[BUF_SIZE];
	int strLen;

	if(argc!=3){
		printf("Usage : %s <GROUP IP> <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	recv_sock=socket(PF_INET,SOCK_DGRAM,0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(argv[2]));
	addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(recv_sock,(SOCKADDR*)&addr,sizeof(addr))==SOCKET_ERROR)
		ErrorHandling("bind error");

	join_addr.imr_multiaddr.s_addr=inet_addr(argv[1]);
	join_addr.imr_interface.s_addr=htonl(INADDR_ANY);

	if(setsockopt(recv_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&join_addr,sizeof(join_addr))==SOCKET_ERROR)
		ErrorHandling("setsockopt error");

	strLen=recvfrom(recv_sock,buf,BUF_SIZE-1,0,NULL,0);
	buf[strLen]=0;
	fputs(buf,stdout);
	
	closesocket(recv_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}