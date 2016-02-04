#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024

int main(int argc,char**argv){
	int serv_sock,client_sock;
	char message[BUF_SIZE];
	int str_len,i;
	
	struct sockaddr_in serv_addr,client_addr;
	socklen_t client_addr_size;
	FILE *readfp,*writefp;
	
	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
		fputs("bind error",stderr);
		exit(1);
	}
	if(listen(serv_sock,5)==-1){
		fputs("listen error",stderr);
		exit(1);
	}
	client_addr_size=sizeof(client_addr);
	for(i=0;i<5;i++){
		client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&client_addr_size);
		if(client_sock==-1){
			fputs("client_sock error",stderr);
			exit(1);
		}
		else printf("connected client %d \n",client_sock);
		readfp=fdopen(client_sock,"r");
		writefp=fdopen(client_sock,"w");
		while(!feof(readfp)){
			fgets(message,BUF_SIZE,readfp);
			fputs(message,writefp);
			fflush(writefp);
		}
		fclose(writefp);
		fclose(readfp);
	}
	close(serv_sock);
	return 0;
}
	
