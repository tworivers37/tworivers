/*
	약수의 합
*/

#include<iostream>
using namespace std;
int n=24;


//값이 크면 비효율적
void solv1(){
	int result=0;
	for(int i=1;i<=n;i++) if(n%i==0) result+=i;
	
	cout<<result<<endl;
}

//2이상 n미만의 자연수들 중 가장 큰 n의 약수는 n/2를 넘지 않는다.
void solv2(){
	int result=0;
	//for의 n/2가 반복 될 때마다 계산함.
	//for(int i=2;i<=n/2;i++) if(n%i==0)result+=i;
	for(int i=1,tmp=n/2;i<=tmp;i++) if(n%i==0)result+=(i);
	result+=n;
	cout<<result<<endl;
}

//자연수 n의 약수들 중 두 약수의 곱은 n이되는 약수 두 개는 반드시 존재.
//단, n이 완전제곱수일 경우에는 두 약수가 같을 수 있다.
//ex) 10의 약수 -> 1,2,5,10 -> 1*10, 2*5 => 10
//ex) 16(완전제곱수)의 약수 -> 1,2,4,8,16-> 1*16, 2*8, 4*4 =>16
//2부터 sqrt(n) 까지만 계산하면됨.
void solv3(){
	int result=0,i;
	//i<sqrt(n) -> i*i<n
	for(i=1;i*i<n;i++) if(n%i==0) result+=(i+n/i);
	if(i*i==n) result+=i;

	cout<<result<<endl;
}

int main(){
	solv1();
	solv2();
	solv3();
	return 0;
}
