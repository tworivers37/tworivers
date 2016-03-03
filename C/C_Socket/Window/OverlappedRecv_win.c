#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

#define BUF_SIZE 1024

void ErrorHandling(char *msg);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET listenSock,recv_sock;
	SOCKADDR_IN listenAddr,recvAddr;
	int recv_addr_size;

	WSABUF dataBuf;
	WSAEVENT eventObject;
	WSAOVERLAPPED overlapped;

	char buf[BUF_SIZE];
	int recvBytes=0,flags=0;

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	listenSock=WSASocket(PF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	memset(&listenAddr,0,sizeof(listenAddr));
	listenAddr.sin_family=AF_INET;
	listenAddr.sin_port=htons(atoi(argv[1]));
	listenAddr.sin_addr.s_addr=htonl(INADDR_ANY);

	puts("bind");
	if(bind(listenSock,(SOCKADDR*)&listenAddr,sizeof(listenAddr))==SOCKET_ERROR) ErrorHandling("bind error");

	puts("listen");
	if(listen(listenSock,5)==SOCKET_ERROR) ErrorHandling("listen error");
	
	puts("accept");
	recv_addr_size=sizeof(recvAddr);
	recv_sock=accept(listenSock,(SOCKADDR*)&recvAddr,&recv_addr_size);

	puts("WSACreateEvent");
	eventObject=WSACreateEvent();
	memset(&overlapped,0,sizeof(overlapped));
	overlapped.hEvent=eventObject;
	dataBuf.len=BUF_SIZE;
	dataBuf.buf=buf;

	puts("WSARecv");
	if(WSARecv(recv_sock,&dataBuf,1,&recvBytes,&flags,&overlapped,NULL)==SOCKET_ERROR){
		if(WSAGetLastError()==WSA_IO_PENDING){ //데이터 수신이 진행 중
			puts("Background data receive");
			WSAWaitForMultipleEvents(1,&eventObject,TRUE,WSA_INFINITE,FALSE);
			WSAGetOverlappedResult(recv_sock,&overlapped,&recvBytes,FALSE,NULL);
		}
		else ErrorHandling("WSARecv error");
	}

	printf("Received message : %s \n",buf);
	WSACloseEvent(eventObject);
	closesocket(recv_sock);
	closesocket(listenSock);
	WSACleanup();

}
void ErrorHandling(char*msg){
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}