#include<stdio.h>
#include<unistd.h>

int main(){
	int fd1,fd2;
	char str1[]="Hello\n";
	char str2[]="good\n";
	
	fd1=dup(1); //표준출력 파일디스크립터를 복사.
	fd2=dup2(fd1,7); //fd1파일디스크립터를 정수값 7을 가진 파일디스크립터로 복사.
	printf("fd1 : %d . fd2 : %d\n",fd1,fd2);
	write(fd1,str1,sizeof(str1));//표준 출력을 복사한 파일디스크립터
	write(fd2,str2,sizeof(str2));
	
	close(fd1);
	close(fd2);

	write(1,str1,sizeof(str1)); //표준 출력
	close(1);//표준 출력 종료
	write(1,str2,sizeof(str2));//표준 출력이 종료되어 출력이 이뤄지지 않음.
	return 0;
}
	
