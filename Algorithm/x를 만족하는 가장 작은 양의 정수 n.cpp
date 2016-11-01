/*
다음 식에서 ‘*’ 문자는 ‘+’ 또는 ‘-’ 연산자를 할당할 수 있으며, x를 만족하는 가장 작은 양의 정수 n을 구하시오.
* 1 * 2 * . . . * n = x
예를 들면 x = 12일 경우 이를 만족하는 가장 작은 양의 정수 n = 7이다.
- 1 + 2 + 3 + 4 + 5 + 6 - 7 = 12

[입력 방식]
첫 줄에는 테스트 총 개수가 주어진다.
입력된 각 정수 x는 (0 ≤ |x| ≤ 1000000000)을 만족한다.
입력된 각 정수 x는 한 줄에 하나의 값으로 주어진다.

[출력 방식]
주어진 x를 만족하는 가장 작은 양의 정수 n (1 ≤ n)을 출력한다.
각각의 결과는 한 줄로 나누어 출력한다.

[입력 샘플]
2
12
-3646397

[출력 샘플]
7
2701
*/

#include<iostream>
#include<cmath>
using namespace std;

long long int sum(long long int n){
	return (n*(n+1))/2;
}

long long int solv(long long int x){
	int i=0;
	long long int s;
	int sub;

	if(x<0) x=abs(x); //음수 일 때

	while((s=sum(++i))<x); //x 보다 커지는 최초의 i 값
	if(s==x) return i;
	

	//1+2+3....= s 에서 1을 -1 로 바꾸게되면 s의 값은 s-2가 되는 것을 이용.
	//2를 -2 로 바꾸면 s-4
	//(i+1)-(i+2) = -1 임.
	sub=x-s;
	if(abs(sub)%2==0) return i;
	else return i+2;
}
int main(){
	cout<<solv(7)<<endl;
	cout<<solv(12)<<endl;
	cout<<solv(19)<<endl;
	cout<<solv(-3646397)<<endl;
	cout<<solv(1000000000)<<endl;
	cout<<solv(-1000000000)<<endl;
	return 0;
}
