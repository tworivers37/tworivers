#include<iostream>
using namespace std;

void rect(int cnt){
	int *x=new int[cnt*3];
	int *y=new int[cnt*3];
	for(int i=0;i<cnt*3;i++) cin>>x[i]>>y[i];
	for(int i=0;i<cnt;i++)
		cout<<(x[0+i*3]^x[1+i*3]^x[2+i*3])<<" "<<(y[0+i*3]^y[1+i*3]^y[2+i*3])<<endl;
}
int main(){
	int cnt;
	cin>>cnt;
	rect(cnt);
	return 0;
}
