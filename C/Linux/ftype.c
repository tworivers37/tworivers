#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char**argv){
	int i;
	struct stat buf;
	
	for(i=1;i<argc;++i){
		printf("%s: ",argv[i]);
		if(lstat(argv[1],&buf)<0){
			perror("lstat()");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			printf("Regular file\n");
		if(S_ISDIR(buf.st_mode))
			printf("Directory file\n");
		if(S_ISCHR(buf.st_mode))
			printf("Character device file\n");
		if(S_ISBLK(buf.st_mode))
			printf("Block device file\n");
		if(S_ISLNK(buf.st_mode))
			printf("Symbolic file\n");

	}
	exit(0);
	return 0;
}
