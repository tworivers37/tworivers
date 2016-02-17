#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char*message);

void main(int argc,char**argv){
	WSADATA wsaData;
	SOCKET sock;
	char message[BUF_SIZE];
	int strLen,client_addr_size;
	SOCKADDR_IN serv_addr,client_addr;

	if(argc!=3){
		printf("Usage : %s <IP> <PORT>\n",argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0) ErrorHandling("WSAStartup error");

	sock=socket(PF_INET,SOCK_DGRAM,0);
	if(sock==INVALID_SOCKET) ErrorHandling("socket error");

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);

	while(1){
		fputs("Insert message(q to quit) : ",stdout);
		fgets(message,sizeof(message),stdin);
		if(!strcmp("q\n",message) || !strcmp("Q\n",message)) break;
		sendto(sock,message,strlen(message),0,(SOCKADDR*)&serv_addr,sizeof(serv_addr));
		client_addr_size=sizeof(client_addr);
		strLen=recvfrom(sock,message,BUF_SIZE,0,(SOCKADDR*)&client_addr,&client_addr_size);
		message[strLen]=0;
		printf("Message from server : %s \n",message);
	}
	closesocket(sock);
	WSACleanup();
}
void ErrorHandling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}