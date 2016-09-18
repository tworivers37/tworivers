/*
n-queen
전산학에서 백트래킹 문제로 n-queen problem이 유명하다.
이 문제는 n*n체스 보드판에 n개의 queen을 서로 공격하지 못하도록 배치하는 방법
을 찾아내는 문제이다.
아래 그림은 n이 4일 경우 queen을 서로 공격하지 못하게 배치한 한 예를 나타낸
다.
체스판 크기 및 queen의 수를 나타내는 n을 입력받아서 서로 공격하지 못하도록
배치하는 총 방법의 수를 구하는 프로그램을 작성하시오.

입력
정수 n이 입력으로 들어온다.( 3 <= n <= 9 )
출력
서로 다른 총 경우의 수를 출력한다.
입력 예 출력 예
4 2

*/
#include<iostream>

using namespace std;

const int n=4;// n * n
bool col[n]={false,};
bool leftCross[n*2]={false,},rightCross[n*2]={false,};
int ans=0;

//leftCross -> n+(r-c)
//rightCorss -> r+c

void nQ(int r){
	if(r>=n){
		ans++;
		return;
	}
	for(int i=0;i<n;i++){
		if(!col[i] && !leftCross[n+(r-i)] && !rightCross[r+i]){
			col[i]=leftCross[n+(r-i)]=rightCross[r+i]=true;
			nQ(r+1);
			col[i]=leftCross[n+(r-i)]=rightCross[r+i]=false;
		}
	}
}

int main(){
	
	nQ(0);
	cout<<ans<<endl;
	return 0;
}
