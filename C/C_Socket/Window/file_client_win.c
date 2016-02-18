#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	FILE *fp;
	char buf[BUF_SIZE];
	int readCnt;
	SOCKADDR_IN serv_addr;

	if(argc!=3){
		printf("Usage : %s <IP> <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	fp=fopen("receive.dat","wb");
	sock=socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);

	connect(sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr));
	
	while((readCnt=recv(sock,buf,BUF_SIZE,0))!=0) fwrite((void*)buf,1,readCnt,fp);

	puts("Received file data");
	send(sock,"Thank you",10,0);
	fclose(fp);
	closesocket(sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}