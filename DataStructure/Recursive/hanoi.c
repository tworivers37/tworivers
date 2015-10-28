#include"common.h"

void hanoi(int n,char from,char by,char to){

	if(n==1)
		printf("%d : %c -> %c\n",n,from,to);
	else{
		hanoi(n-1,from,to,by);
		printf("%d : %c -> %c\n",n,from,to);
		hanoi(n-1,to,from,by);
	}

}