#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<signal.h>
#include<arpa/inet.h>
#include<string.h>

#define BUF 30
void error_handling(char *message);
void childProc(int sig);

int main(int argc,char **argv){
	int serv_sock,client_sock;
	struct sockaddr_in serv_addr,client_addr;

	pid_t pid;
	struct sigaction act;
	socklen_t addr_size;
	int str_len,state;
	char buf[BUF];
	if(argc!=2){
		printf("Usage : %s <port> \n",argv[0]);
		exit(1);
	}
	act.sa_handler=childProc;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	state=sigaction(SIGCHLD,&act,0);
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1) error_handling("bind error");
	if(listen(serv_sock,5)==-1) error_handling("listen error");
	while(1){
		addr_size=sizeof(client_addr);
		client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&addr_size);
		if(client_sock==-1) continue;
		else puts("new client connected....");
		pid=fork();
		if(pid==-1){
			close(client_sock);
			continue;
		}
		if(pid==0){
			//소켓에 할당된 파일디스크립터가 두 개이면
			//두 개의 파일디스크립터 모두가 소멸 되어야
			//소켓도 소멸이 됨.
			close(serv_sock);//자식에겐 필요 없으므로 닫아줌.
			while((str_len=read(client_sock,buf,BUF))!=0)
				write(client_sock,buf,str_len);
			close(client_sock);
			puts("client disconnected...");
			return 0;
		}
		else close(client_sock);//부모에겐 필요없음.
	}
	close(serv_sock);
	return 0;
}
void childProc(int sig){
	pid_t pid;
	int status;
	pid=waitpid(-1,&status,WNOHANG);
	printf("removed proc id : %d \n",pid);
}
void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
		
