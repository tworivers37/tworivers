#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET serv_sock,client_sock;
	FILE *fp;
	char buf[BUF_SIZE];
	int readCnt;
	SOCKADDR_IN serv_addr,client_addr;
	int client_addr_size;

	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	fp=fopen("file_server_win.c","rb");
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	bind(serv_sock,(SOCKADDR*)&serv_addr,sizeof(serv_addr));
	listen(serv_sock,5);

	client_addr_size=sizeof(client_addr);
	client_sock=accept(serv_sock,(SOCKADDR*)&client_addr,&client_addr_size);

	while(1){
		readCnt=fread((void*)buf,1,BUF_SIZE,fp);
		if(readCnt<BUF_SIZE){
			send(client_sock,(char*)&buf,readCnt,0);
			break;
		}
		send(client_sock,(char*)&buf,BUF_SIZE,0);
	}
	shutdown(client_sock,SD_SEND);
	recv(client_sock,(char*)buf,BUF_SIZE,0);
	printf("Message from client : %s \n",buf);
	fclose(fp);
	closesocket(client_sock);
	closesocket(serv_sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}