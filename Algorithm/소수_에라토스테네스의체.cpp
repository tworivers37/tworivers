#include<iostream>
using namespace std;
void main(){
	int n;
	int *arr;
	
	cout<<"input : ";
	cin>>n;

	arr=new int[n];
	memset(arr,0,n);
	
	//에라토스테네스의 체
	arr[0]=arr[1]=-1; //-1 은 소수가 아님.
	for(int i=2,j=0;i<=n;i++){
		if(arr[i]==-1) continue; // i 는 소수가 아니므로 다음
		j=i;
		while((j+=i)<=n) arr[j]=-1; // j 의 배수는 소수가 아님. (ex j=2; 4,6,8, ...)
	}

	for(int i=0;i<=n;i++){
		if(arr[i]!=-1) cout<<i<<" ";
	}
	cout<<endl;
}