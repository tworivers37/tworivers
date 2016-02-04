#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>

#define BUF_SIZE 30

void error_handling(char*message);
void read_proc(int sig);

int main(int argc,char **argv){
 	pid_t pid;
	int serv_sock,client_sock;
	struct sockaddr_in serv_addr,client_addr;
	int fds[2];
	struct sigaction sig;
	socklen_t addr_size;
	int str_len;
	char buf[BUF_SIZE];	
	FILE *fp;
	char msgbuf[BUF_SIZE];
	int i,len;
	
	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	sig.sa_handler=read_proc;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags=0;
	sigaction(SIGCHLD,&sig,0);
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind error");
	if(listen(serv_sock,5)==-1)
		error_handling("listen error");
	pipe(fds);
	pid=fork();
	if(pid==0){
		fp=fopen("echo_msg.txt","wt");
		for(i=0;i<5;i++){//5번 입력이 있어야 파일에 저장이 완료됨.
			len=read(fds[0],msgbuf,BUF_SIZE);
			fwrite((void*)msgbuf,1,len,fp);
		}
		fclose(fp);
		return 0;
	}
	while(1){
		addr_size=sizeof(client_addr);
		client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&addr_size);
		if(client_sock==-1) continue;
		else puts("new client connected...");
		pid=fork();
		if(pid==0){
			close(serv_sock);
			while((str_len=read(client_sock,buf,BUF_SIZE))!=0){
				write(client_sock,buf,str_len);
				write(fds[1],buf,str_len);
			}
			close(client_sock);
			puts("client disconnected ...");
			return 0;
		}
		else close(client_sock);
	}
	close(serv_sock);
	return 0;
}
void read_proc(int sig){
	int status;
	pid_t pid=waitpid(-1,&status,WNOHANG);
	printf("removed proc : %d \n",pid);
}
void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
	
