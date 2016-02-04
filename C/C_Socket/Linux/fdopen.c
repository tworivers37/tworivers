#include<stdio.h>
#include<fcntl.h>

int main(){
	FILE *fp;
	int fd=open("data.dat",O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1){
		fputs("file open error",stderr);
		return -1;
	}
	fp=fdopen(fd,"w");// 파일디스크립터를 FILE 구조체의 포인터로 변경.
	fputs("fdopen\n",fp);
	fclose(fp);
	return 0;
}
