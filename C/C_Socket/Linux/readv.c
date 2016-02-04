#include<stdio.h>
#include<sys/uio.h>

#define BUF_SIZE 30

int main(int argc,char**argv){
	struct iovec vec[2];
	char buf1[BUF_SIZE]={0,};
	char buf2[BUF_SIZE]={0,};
	int str_len;
	
	vec[0].iov_base=buf1;
	vec[0].iov_len=5;
	vec[1].iov_base=buf2;
	vec[1].iov_len=BUF_SIZE;
	
	//파일디스크립터,iovec 구조체의 배열,배열의 갯수
	//iovec 구조체 ->iov_base,iov_len 으로 구성
	//iov_base는 버퍼주소(void* 타입)
	//iov_len 은 버ㅓ퍼의 크기
	str_len=readv(0,vec,2);
	printf("Read bytes : %d\n",str_len);
	printf("First message : %s\n",buf1);
	printf("Second message : %s\n",buf2);
	return 0;
}
