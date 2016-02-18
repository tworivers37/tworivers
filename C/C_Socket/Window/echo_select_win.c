#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 1024
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock,client_sock;
	SOCKADDR_IN serv_addr,client_addr;
	TIMEVAL timeout;
	fd_set reads,cpyReads;
	int addr_size;
	int strLen,fdNum,i;
	char buf[BUF_SIZE];

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr))==SOCKET_ERROR)
		ErrorHandling("bind error");

	if(listen(serv_sock,5)==SOCKET_ERROR) ErrorHandling("listen error");

	FD_ZERO(&reads);
	FD_SET(serv_sock,&reads);

	while(1){
		cpyReads=reads;
		timeout.tv_sec=3;
		timeout.tv_usec=30;

		if((fdNum=select(0,&cpyReads,0,0,&timeout))==SOCKET_ERROR) break;

		if(fdNum==0) continue;

		for(i=0;i<reads.fd_count;i++){
			if(FD_ISSET(reads.fd_array[i],&cpyReads)){
				if(reads.fd_array[i]==serv_sock){
					addr_size=sizeof(client_addr);
					client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&addr_size);
					FD_SET(client_sock,&reads);
					printf("connected client : %d \n",client_sock);
				}
				else{
					strLen=recv(reads.fd_array[i],buf,BUF_SIZE-1,0);
					if(strLen==0){
						FD_CLR(reads.fd_array[i],buf,BUF_SIZE-1,0);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client : %d \n",cpyReads.fd_array[i]);
					}
					else
						send(reads.fd_array[i],buf,strLen,0);
				}
			}
		}
	}
	closesocket(serv_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}