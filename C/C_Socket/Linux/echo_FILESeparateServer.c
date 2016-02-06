#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char **argv){
	int serv_sock,client_sock;
	FILE *readFp;
	FILE *writeFp;
	
	struct sockaddr_in serv_addr,client_addr;
	socklen_t client_addr_size;
	char buf[BUF_SIZE];

	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
			exit(1);
	if(listen(serv_sock,5)==-1) exit(1);

	client_addr_size=sizeof(client_addr);
	client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&client_addr_size);
	readFp=fdopen(client_sock,"r");
	//Half-close를 위해서 파일 디스크립터 복사.
	//readFp와 writeFp가 가리키는 파일 디스크립터는 다름.
	writeFp=fdopen(dup(client_sock),"w");
	
	fputs("FROM Server : Hello Client \n",writeFp);
	fputs("SERVER \n",writeFp);
	fputs("Seperate Server \n",writeFp);
	fflush(writeFp);
	
	shutdown(fileno(writeFp),SHUT_WR); //출력 FILE 포인터의 출력 파일디스크립터 종료.
	//readFp가 가리키는 파일 디스크립터랑 다르므로 Half-close 성공.
	fclose(writeFp);

	fgets(buf,sizeof(buf),readFp);//클라이언트가 EOF를 받은 후 보내는 마지막 문자열 읽음.
	fputs(buf,stdout);
	fclose(readFp);
	return 0;
}
