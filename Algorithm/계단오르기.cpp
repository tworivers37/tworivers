/*
계단 오르기
길동이는 n개의 단으로 구성된 계단을 오르려고 한다.
길동이는 계단을 오를 때 기분에 따라서 한 번에 1단 또는 2단을 올라갈 수 있다.
계단의 크기 n이 주어질 때, 길동이가 이 계단을 올라갈 수 있는 모든 경우의 수
를 구하는 프로그램을 작성하시오.
만약 계단이 3개라면 길동이는 1, 1, 1로 올라가는 법과 1, 2로 올라가는 법, 2, 1
로 올라가는 법의 3가지 서로 다른 방법이 있다.
입력
계단의 수 n이 입력된다(단 n은 20보다 작은 자연수).
출력
길동이가 계단을 오르는 모든 방법의 수를 출력한다.

입력 예 출력 예
3 3

*/

#include<iostream>
using namespace std;

int n=100;
__int64 dynamic[100]={0,};

__int64 dfs(int c){
	if(c==n) return 1;
	else if(c>n) return 0;
	
	if(dynamic[c]) return dynamic[c];
	else{
		dynamic[c]=dfs(c+1)+dfs(c+2);
		return dynamic[c];
	}
}
__int64 solv(){
	__int64 cnt=0;
	for(int i=0;i<2;i++)
		cnt+=dfs(i+1);
	return cnt;
}

int main(){
	cout<<solv()<<endl;

	return 0;
}
