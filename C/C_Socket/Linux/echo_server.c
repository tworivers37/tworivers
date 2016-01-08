#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>

#define MESSAGE_SIZE 1024

int main(int argc,char**argv){
	int sSock,cSock;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	socklen_t c_size;
	char message[MESSAGE_SIZE];
	int str_len,i;
	
	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	
	sSock=socket(PF_INET,SOCK_STREAM,0);
	if(sSock==-1) printf("sock err\n");
	
	memset(&s_addr,0,sizeof(s_addr));
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(atoi(argv[1]));
	if(!inet_aton("127.0.0.1",&s_addr.sin_addr)) printf("addr err\n");

	if(bind(sSock,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1)
		printf("bind err\n");
	if(listen(sSock,5)==-1) printf("listen err\n");
	c_size=sizeof(c_addr);
	for(i=0;i<5;i++){
		cSock=accept(sSock,(struct sockaddr*)&c_addr,&c_size);
		if(cSock==-1) printf("cSock err\n");
		else printf("connect %d \n",i+1);
		while((str_len=read(cSock,message,MESSAGE_SIZE))!=0)
			write(cSock,message,str_len);
		close(cSock);
	}
	close(sSock);
	return 0;
}
