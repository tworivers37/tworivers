#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc,char**argv){
	int sock;
	struct sockaddr_in send_addr;
	if(argc!=3){
		printf("Usage : %s <IP> <PORT> \n",argv[0]);
		exit(1);
	}
	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&send_addr,0,sizeof(send_addr));
	send_addr.sin_family=AF_INET;
	send_addr.sin_port=htons(atoi(argv[2]));
	send_addr.sin_addr.s_addr=inet_addr(argv[1]);
	
	if(connect(sock,(struct sockaddr*)&send_addr,sizeof(send_addr))==-1)
		error_handling("connect error");
	
	write(sock,"123",strlen("123"));
	send(sock,"45",strlen("45"),MSG_OOB);
	sleep(1);
	write(sock,"567",strlen("567"));
	send(sock,"890123",strlen("890123"),MSG_OOB);
	close(sock);
	return 0;
}
void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
