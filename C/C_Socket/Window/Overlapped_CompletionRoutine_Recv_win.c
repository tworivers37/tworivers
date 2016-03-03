#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

#define BUF_SIZE 1024
void CALLBACK CompRoutine(DWORD,DWORD,LPWSAOVERLAPPED,DWORD);
void ErrorHandling(char*msg);

WSABUF dataBuf;
char buf[BUF_SIZE];
int recvBytes=0;

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET listenSock,recv_sock;
	SOCKADDR_IN listenAddr,recv_addr;

	WSAOVERLAPPED overlapped;
	WSAEVENT eventObject;
	int idx,recv_addr_size,flags=0;

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

	if(bind(listenSock,(SOCKADDR*)&listenAddr,sizeof(listenAddr)==SOCKET_ERROR)) ErrorHandling("bind error");

	if(listen(listenSock,5)==SOCKET_ERROR) ErrorHandling("listen error");

	recv_addr_size=sizeof(recv_addr);
	recv_sock=accept(listenSock,(SOCKADDR*)&recv_addr,&recv_addr_size);
	if(recv_sock==INVALID_SOCKET) ErrorHandling("accept error");

	memset(&overlapped,0,sizeof(overlapped));
	dataBuf.len=BUF_SIZE;
	dataBuf.buf=buf;
	eventObject=WSACreateEvent(); //dummy

	if(WSARecv(recv_sock,&dataBuf,1,&recvBytes,&flags,&overlapped,CompRoutine)==SOCKET_ERROR)
		if(WSAGetLastError()==WSA_IO_PENDING) puts("Background data receive");
	
	idx=WSAWaitForMultipleEvents(1,&eventObject,FALSE,WSA_INFINITE,TRUE);//alertable wait ป๓ลย
	if(idx==WAIT_IO_COMPLETION) puts("Overlapped IO Completed");
	else ErrorHandling("WSARecv error");

	WSACloseEvent(eventObject);
	closesocket(recv_sock);
	closesocket(listenSock);
	WSACleanup();

}

void CALLBACK CompRoutine(DWORD dwError,DWORD szRecvBytes,LPWSAOVERLAPPED lpOverlapped,DWORD flags){
	if(dwError!=0) ErrorHandling("CompRoutine error");
	else{
		recvBytes=szRecvBytes;
		printf("Received message : %s \n",buf);
	}
}
void ErroorHandling(char*msg){
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}