#include<stdio.h>

void tmpSwap(int *a,int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void noTmpSwap(int *a,int *b){
	*b+=*a;	// b= b+a
	*a=*b-*a; // a= (b+a)-a = b
	*b-=*a; // b= (b+a)-b = a
}

void xorSwap(int *a,int *b){
	*a^=*b; // *a= *a ^ *b
	*b^=*a; // *b= *b ^ (*a ^ *b) = *a
	*a^=*b; // *a= (*a ^ *b) ^ *a = *b
}

void main(){
	int a=10,b=20;
	
	tmpSwap(&a,&b);
	printf("%d %d\n",a,b);

	a=10,b=20;
	noTmpSwap(&a,&b);
	printf("%d %d\n",a,b);
	
	a=10,b=20;
	xorSwap(&a,&b);
	printf("%d %d\n",a,b);
}