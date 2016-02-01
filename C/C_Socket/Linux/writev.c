#include<stdio.h>
#include<sys/uio.h>

int main(int argc, char**argv){
	struct iovec vec[2];
	char buf1[]="abcdefg";
	char buf2[]="1234567";
	int str_len;
	vec[0].iov_base=buf1;
	vec[0].iov_len=3;
	vec[1].iov_base=buf2;
	vec[1].iov_len=5;
	//파일디스크립터,iovec 구조체의 배열,배열의 갯수
	//iovec 구조체 ->iov_base,iov_len 으로 구성
	//iov_base는 버퍼주소(void* 타입)
	//iov_len 은 버ㅓ퍼의 크기
	str_len=writev(1,vec,2);
	puts("");
	printf("Write bytes : %d \n",str_len);
	return 0;
}
