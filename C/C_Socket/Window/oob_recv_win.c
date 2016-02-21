#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET accept_sock,recv_sock;
	SOCKADDR_IN recv_addr,send_addr;
	int send_addr_size,strLen;
	char buf[BUF_SIZE];
	int result;

	fd_set read,except,readCopy,exceptCopy;
	struct timeval timeout;

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[1]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)ErrorHandling("WSAStartup error");

	accept_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&recv_addr,0,sizeof(recv_addr));
	recv_addr.sin_family=AF_INET;
	recv_addr.sin_port=htons(atoi(argv[1]));
	recv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(accept_sock,(SOCKADDR*)&recv_addr,sizeof(recv_addr))==SOCKET_ERROR)
		ErrorHandling("bind error");

	if(listen(accept_sock,5)==SOCKET_ERROR)
		ErrorHandling("listen error");

	send_addr_size=sizeof(send_addr);
	recv_sock=accept(accept_sock,(SOCKADDR*)&send_addr,&send_addr_size);

	FD_ZERO(&read);
	FD_ZERO(&except);
	FD_SET(recv_sock,&read);
	FD_SET(recv_sock,&except);

	while(1){
		readCopy=read;
		exceptCopy=except;

		timeout.tv_sec=5;
		timeout.tv_usec=5000;

		result=select(0,&readCopy,0,&exceptCopy,&timeout);
		if(result>0){
			if(FD_ISSET(recv_sock,&exceptCopy)){ //MSG_OOB 는 예외상황에 들어감.
				strLen=recv(recv_sock,buf,BUF_SIZE-1,MSG_OOB);
				buf[strLen]=0;
				printf("Urgent message : %s \n",buf);
			}

			if(FD_ISSET(recv_sock,&readCopy)){
				strLen=recv(recv_sock,buf,BUF_SIZE-1,0);
				if(strLen==0){
					break;
					closesocket(recv_sock);
				}
				else{
					buf[strLen]=0;
					puts(buf);
				}
			}

		}
	}
	closesocket(accept_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}