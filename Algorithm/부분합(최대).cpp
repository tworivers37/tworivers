/*
maximum sum(S)
n개의 원소로 이루어진 집합이 있다. 이 집합에서 최대로 가능한 부분합을 구하는
것이 문제이다.
부분합이란 n개의 원소 중 i번째 원소로부터 j번째 원소까지의 연속적인 합을 의미
한다(단, 1 < i <= j <= n ). 만약 다음과 같이 6개의 원소로 이루어진 집합이 있다
고 가정하자.
6 -7 3 -1 5 2
이 집합에서 만들어지는 부분합 중 최댓값은 3번째 원소부터 6번째 원소까지의 합
인 9이다.
입력
첫 줄에 원소의 수를 의미하는 정수 n이 입력되고, 둘째 줄에 n개의 정수가 공백
으로 구분되어 입력된다.
(단, 2 <= n <= 100 , 각 원소의 크기는 -1000부터 1000 사이의 정수이다.)
출력
주어진 집합에서 얻을 수 있는 최대 부분합을 출력한다.
입력 예 
출력 예

6
6 ‐7 3 ‐1 5 2

9
*/
#include<iostream>	
using namespace std;

const int n=16;
const int arr[n]={3,5,7,-2,6,-13,-9,-7,-6,-12,1,2,21,-23,6,11};

int solv(){
	int sum=0,max=-1;

	for(int i=0;i<n;i++){
		sum+=arr[i];
		if(sum>max)max=sum; 
		if(sum<0) sum=0;	//총 합이 음수가 되면 0으로 만듦.
							//합이 음수가 되어 0이 되면 하나의 구간으로 구분되고 그 때의
							//max 값은 그 구간에서의 최대 값이 된다.
	}
	return max;
}
int main(){
	cout<<solv()<<endl;
	return 0;
}
