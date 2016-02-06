#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_SIZE 1024

int main(int argc,char**argv){
	int sock;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;

	FILE *readFp;
	FILE *writeFp;
	
	sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	
	connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	readFp=fdopen(sock,"r");//표준 입력 함수 호출을 위해 sock을 통해 FILE 포인터 생성
	writeFp=fdopen(sock,"w");
	
	while(1){
		if(fgets(buf,sizeof(buf),readFp)==NULL) //리턴값이 NULL 이면 EOF 를 받은 것.
			break;
		fputs(buf,stdout);
		fflush(stdout);
	}
	fputs("FROM Client : Thank you \n",writeFp); //서버로 EOF 를 수신 후 마지막 문자열 전송.
	fflush(writeFp);
	fclose(writeFp);
	fclose(readFp);
	return 0;
}
