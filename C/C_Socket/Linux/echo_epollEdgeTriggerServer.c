#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50

void setnonblockingmode(int fd);
void error_handling(char*message);

int main(int argc,char**argv){
	int serv_sock,client_sock;
	socklen_t addr_size;
	struct sockaddr_in serv_addr,client_addr;
	int str_len,i;
	char buf[BUF_SIZE];
	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd,event_cnt;
		
	if(argc!=2){
		printf("Usage : %s <PORT> \n",argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
		error_handling("bind error");
	if(listen(serv_sock,5)==-1)
		error_handling("listen error");

	epfd=epoll_create(EPOLL_SIZE);
	ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	
	setnonblockingmode(serv_sock);
	event.events=EPOLLIN;
	event.data.fd=serv_sock;
	epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);
	while(1){
		puts("epoll_wait");
		event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
		if(event_cnt==-1){
			puts("epoll_wait error");
			break;
		}
		puts("return epoll_wait");
		for(i=0;i<event_cnt;i++){
			puts("event_cnt for");

			if(ep_events[i].data.fd==serv_sock){
				addr_size=sizeof(client_addr);
				client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&addr_size);
				//non-blocking이 없으면 read에서 계속 대기하게됨.
				//그래서 하나의 client의 요청만 계속 처리 하는 형태로 동작함.
				//non-blocking이 있으면 read 에서 blocking 되지 않고 지나가게 되어 epoll_wait 함수 에서 대기하게 됨.
				//그래서 다른 client 의 요청을 처리 할 수 있음.
				//(다른 파일 디스크립터의 변화를 감지하게 되기에)
				setnonblockingmode(client_sock);
				event.events=EPOLLIN|EPOLLET;
				event.data.fd=client_sock;
				epoll_ctl(epfd,EPOLL_CTL_ADD,client_sock,&event);
				printf("connected client : %d \n",client_sock);
			}
			else{
				while(1){
					puts("read");
					str_len=read(ep_events[i].data.fd,buf,BUF_SIZE);
					puts("non test");
					
					if(str_len==0){
						puts("str = 0");

						epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
						close(ep_events[i].data.fd);
						printf("closed client : %d\n",ep_events[i].data.fd);
						break;
					}
					else if(str_len<0){
						puts("str < 0");
	
						if(errno==EAGAIN) break;
					}
					else{
						puts("write");
						write(ep_events[i].data.fd,buf,str_len);
					}
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}
void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
void setnonblockingmode(int fd){
	int flag=fcntl(fd,F_GETFL,0);
	fcntl(fd,F_SETFL,flag|O_NONBLOCK);
}	
