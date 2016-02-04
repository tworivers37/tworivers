#include<stdio.h>
#include<fcntl.h>

int main(){
	FILE *fp;
	int fd=open("data.dat",O_WRONLY|O_CREAT|O_TRUNC);
	if(fd==-1){
		fputs("file open error",stderr);
		return -1;
	}
	printf("First file des : %d\n",fd);
	fp=fdopen(fd,"w");
	fputs("fileno",fp);
	printf("Second file des : %d\n",fileno(fp));
	fclose(fp);
	return 0;
}
