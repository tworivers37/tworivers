#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
#include<WS2tcpip.h> //IP_MULTICAST_TTL option

#define TTL 64
#define BUF_SIZE 30

void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET send_sock;
	SOCKADDR_IN mul_addr;
	int timeLive=TTL;
	char buf[BUF_SIZE]="MULTICAST SENDER";

	if(argc!=3){
		printf("Usage : %s <GROUP IP> <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	send_sock=socket(PF_INET,SOCK_DGRAM,0);
	memset(&mul_addr,0,sizeof(mul_addr));
	mul_addr.sin_family=AF_INET;
	mul_addr.sin_port=htons(atoi(argv[2]));
	mul_addr.sin_addr.s_addr=htonl(atoi(argv[1]));

	setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,(void*)&timeLive,sizeof(timeLive));

	sendto(send_sock,buf,strlen(buf),0,(SOCKADDR*)&mul_addr,sizeof(mul_addr));

	closesocket(send_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}