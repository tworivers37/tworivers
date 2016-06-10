#include<iostream>

using namespace std;

//dynamic fibonacci
//mem -> initialize : -1
int fibonacci_dynamic(int n,int *mem){
	if(mem[n]>0) return mem[n];
	else if(n==1 || n==2){
		mem[n]=1;
		return mem[n];
	}
	else{
		mem[n]=fibonacci_dynamic(n-2,mem)+fibonacci_dynamic(n-1,mem);
		return mem[n];
	}
}

int fibonacci_dynamic_nr(int n){
	int *mem=new int[n];
	mem[1]=1;
	mem[2]=1;

	for(int i=3;i<=n;i++) mem[i]=mem[i-2]+mem[i-1];
	return mem[n];
}

int main(){
	int mem[50]={-1,};
	for(int i=0;i<50;i++)mem[i]=-1;

	cout<<fibonacci_dynamic(6,mem)<<endl;
	cout<<fibonacci_dynamic_nr(6)<<endl;

	return 0;
}