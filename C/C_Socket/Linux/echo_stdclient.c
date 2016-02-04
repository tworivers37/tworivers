#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024

int main(int argc,char**argv){
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in sock_addr;

	FILE *readfp;
	FILE *writefp;
	if(argc!=3){
		printf("Usage : %s <IP> <PORT>\n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&sock_addr,0,sizeof(sock_addr));
	sock_addr.sin_family=AF_INET;
	sock_addr.sin_port=htons(atoi(argv[2]));
	sock_addr.sin_addr.s_addr=inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&sock_addr,sizeof(sock_addr))==-1){
		fputs("connect error",stderr);
		exit(1);
	}
	else printf("connected.....\n");
	
	readfp=fdopen(sock,"r");
	writefp=fdopen(sock,"w");
	while(1){
		fputs("Input message(Q to quit) : ",stdout);
		fgets(message,BUF_SIZE,stdin);
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")) break;
		//표준 입출력 함수는 문자열 단위라 message 끝에 0을 따로 
		//안붙여줘도 됨.	
	
		fputs(message,writefp);
		fflush(writefp);
		fgets(message,BUF_SIZE,readfp);
		printf("Message from server : %s\n",message);
	}
	fclose(readfp);
	fclose(writefp);
	return 0;
}

