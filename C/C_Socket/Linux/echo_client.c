#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MESSAGE_SIZE 1024

int main(int argc,char**argv){
	int sock;
	char message[MESSAGE_SIZE];
	int str_len;
	struct sockaddr_in s_addr;
	
	if(argc!=3){
		printf("Usage : %s <IP> <PORT>\n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1) printf("sock err\n");
	
	memset(&s_addr,0,sizeof(s_addr));
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(atoi(argv[2]));
	if(!inet_aton(argv[1],&s_addr.sin_addr)) printf("addr err\n");
	
	if(connect(sock,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1)
		printf("connect err\n");
	else printf("connected ....\n");
	
	while(1){
		fputs("Input Message(Q to quit) : ",stdout);
		fgets(message,MESSAGE_SIZE,stdin);
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")) break;
		
		write(sock,message,strlen(message));
		str_len=read(sock,message,MESSAGE_SIZE-1);
		message[str_len]=0;
		printf("Message Echo : %s \n",message);
	}
	close(sock);
	return 0;
}
