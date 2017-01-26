#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>

using namespace std;

int main(){
	char buffer[256];
	DIR *dir;
	struct dirent *dentry;

	getcwd(buffer,256);
	cout<<buffer<<endl;
	
	mkdir("apple",0755);
	mkdir("banana",0755);
	chdir("apple");
	getcwd(buffer,256);
	cout<<buffer<<endl;

	close(open("data1.txt",O_CREAT|O_RDWR,0644));
	close(open("data2.txt",O_CREAT|O_RDWR,0644));

	chdir("..");
	rmdir("apple");// fail
	rmdir("banana");

	dir=opendir("apple");
	while(dentry=readdir(dir)){
		cout<<dentry->d_name<<endl;
	}
	rewinddir(dir);
	cout<<"[Rewind directory]\n";
	if(dentry=readdir(dir))
		cout<<dentry->d_name<<endl
;
	closedir(dir);

	return 0;
}
