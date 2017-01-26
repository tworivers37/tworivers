#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

using namespace std;

int main(){
	char *origin="manage.txt";
	char *hard="manage.txt.hard";
	char *soft="manage.txt.soft";

	int fd,retval;
	mode_t oldmask;
	char buffer[1024];
	int nRead;
	struct stat fileInfo;
	
	oldmask=umask(0377); //011 111 111

	fd=open(origin,O_CREAT, 0755);//111 101 101
	close(fd);

	//111 101 101	 111 101 101
	//011 111 111 -> 100 000 000
	//		 100 000 000

	if((retval=access(origin,W_OK))==-1){
		cerr<<origin<<" is not writable\n";
		chmod(origin,0644);
	}
	
	link(origin,hard);
	symlink(origin,soft);
	rename(hard,"manage.hard.new");
	
	nRead=readlink(soft,buffer,1024);
	write(1,buffer,nRead);
	cout<<endl;
	
	stat(origin,&fileInfo);
	cout<<origin<<endl;
	cout<<"file mode : "<<fileInfo.st_mode<<endl;
	cout<<"file size : "<<fileInfo.st_size<<endl;
	cout<<"number of blocks : "<<fileInfo.st_blocks<<endl;
	

	return 0;
}
