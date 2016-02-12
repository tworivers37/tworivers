#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>

//#define BUF_SIZE 100
#define BUF_SIZE 4 
#define EPOLL_SIZE 50

void error_handling(char*message);

int main(int argc,char**argv){
	int serv_sock,client_sock;
	struct sockaddr_in serv_addr,client_addr;
	socklen_t addr_size;
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
	
	epfd=epoll_create(EPOLL_SIZE);//fd저장소 생성(os 내)
	ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);//발생된 이벤트를 담기위한 배열.
	
	event.events=EPOLLIN;
	event.data.fd=serv_sock;//발생한 이벤트의 fd 구분을 위함.
	epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);//저장소에 추가
	
	while(1){
		puts("epoll_wait");
		event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);//fd 변화 대기.
		if(event_cnt==-1){
			puts("epoll_wait error");
			break;
		}
		for(i=0;i<event_cnt;i++){
			puts("event_cnt for");
			if(ep_events[i].data.fd==serv_sock){
				addr_size=sizeof(addr_size);
				client_sock=accept(serv_sock,(struct sockaddr*)&client_addr,&addr_size);
				event.events=EPOLLIN;
				event.data.fd=client_sock;
				epoll_ctl(epfd,EPOLL_CTL_ADD,client_sock,&event);
				printf("connected client : %d \n",client_sock);
			}
			else{
				puts("read");
				//버퍼 크기가 4바이트라 긴 데이터는 한번에 read가 안됨.
				//메시지를 수신 할 때마다 이벤트 등록이 여러번 이뤄짐.버퍼에 데이터가 남아 있으므로
				//이로 인해 epoll_wait 가 다수 호출됨.		
				str_len=read(ep_events[i].data.fd,buf,BUF_SIZE);
				if(str_len==0){
					puts("str_len = 0");
					epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
					close(ep_events[i].data.fd);
					printf("closed client : %d\n",ep_events[i].data.fd);
				}
				else{
					puts("write");
					write(ep_events[i].data.fd,buf,str_len);
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}
void error_handling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
