#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>
void ErrorHandling(char*message);
void ShowSocketBufferSize(SOCKET sock);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	int sendBuf,recvBuf,state;
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	sock=socket(PF_INET,SOCK_STREAM,0);
	ShowSocketBufferSize(sock);

	sendBuf=1024*3;
	recvBuf=1024*3;
	state=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&recvBuf,sizeof(recvBuf));
	if(state==SOCKET_ERROR) ErrorHandling("setsockopt error");

	ShowSocketBufferSize(sock);
	closesocket(sock);
	WSACleanup();
}

void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

void ShowSocketBufferSize(SOCKET sock){
	int sendBuf,recvBuf,state,len;
	len=sizeof(sendBuf);
	state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(char*)&sendBuf,&len);
	if(state==SOCKET_ERROR) ErrorHandling("getsockopt error");
	len=sizeof(recvBuf);
	state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&recvBuf,&len);
	if(state==SOCKET_ERROR) ErrorHandling("getsockopt error");
	printf("Input Buffer size : %d \n",recvBuf);
	printf("Output Buffer size : %d \n",sendBuf);
}