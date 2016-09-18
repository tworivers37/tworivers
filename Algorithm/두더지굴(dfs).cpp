#include<iostream>
using namespace std;
/*
두더지 굴(S)
정올이는 땅속의 굴이 모두 연결되어 있으면 이 굴은 한 마리의 두더지가 사는 집
이라는 사실을 발견하였다.
정올이는 뒷산에 사는 두더지가 모두 몇 마리인지 궁금해졌다. 정올이는 특수 장
비를 이용하여 뒷산의 두더지 굴을 모두 나타낸 지도를 만들 수 있었다.
이 지도는 직사각형이고 가로 세로 영역을 0 또는 1로 표현한다. 0은 땅이고 1은
두더지 굴을 나타낸다. 1이 상하좌우로 연결되어 있으면 한 마리의 두더지가 사는
집으로 정의할 수 있다.

[그림 1] [그림 2]
[그림 2]는 [그림 1]을 두더지 굴로 번호를 붙인 것이다. 특수촬영 사진 데이터를 입
력받아 두더지 굴의 수를 출력하고, 각 두더지 굴의 크기를 오름차순으로 정렬하여
출력하는 프로그램을 작성하시오.

입력
첫 번째 줄에 가로, 세로의 크기를 나타내는 n이 입력된다.(n은 30이하의 자연수)
두 번째 줄부터 n줄에 걸쳐서 n개의 0과 1이 공백으로 구분되어 입력된다.

출력
첫째 줄에 두더지 굴의 수를 출력한다. 둘째 줄부터 각 두더지 굴의 크기를 내림
차순으로 한 줄에 하나씩 출력한다.

입력 예 출력 예

7
0 1 1 0 1 0 0
0 1 1 0 1 0 1
1 1 1 0 1 0 1
0 0 0 0 1 1 1
0 1 0 0 0 0 0
0 1 1 1 1 1 0
0 1 1 1 0 0 0



3
9
8
7

*/


const int n=7;
int mem[n]={0,};
int sizeVal=2;

int arr[n][n]={
	0, 1, 1, 0, 1, 0, 0,
	0, 1, 1, 0, 1, 0, 1,
	1, 1, 1, 0, 1, 0, 1,
	0, 0, 0, 0, 1, 1, 1,
	0, 1, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 0, 0, 0
};

bool check(int x,int y){
	//범위
	if(x<0||x>=n||y<0||y>=n) return false;
	
	//두더지 굴
	if(arr[x][y]==1) return true;
	else return false;
}

void dfs(int x,int y){
	mem[sizeVal]+=1;
	arr[x][y]=sizeVal;

	//up
	if(check(x-1,y)) dfs(x-1,y);
	//down
	if(check(x+1,y)) dfs(x+1,y);
	//left
	if(check(x,y-1)) dfs(x,y-1);
	//right
	if(check(x,y+1)) dfs(x,y+1);
}

void solv(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(check(i,j)){
				dfs(i,j);
				sizeVal++;
			}
		}
	}
}
int main(){
	solv();

	cout<<sizeVal-2<<endl<<endl;

	for(int i=0;i<n;i++) cout<<mem[i]<<" ";
	cout<<endl<<endl;

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
