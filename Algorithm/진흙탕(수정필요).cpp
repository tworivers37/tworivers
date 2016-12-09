/*
진흙탕 탈출하기


정사각형 모양의 진흙탕을 탈출하려고 합니다. 몸을 가장 덜 더럽히고 탈출하는 코드를 작성하세요.
진흙탕은 NxN 크기로 1x1 정사각형 모양의 격자로 이루어져 있습니다. 시작 위치는 왼쪽 아래 모서리의 격자이며, 탈출구는 
오른쪽 위 모서리의 격자입니다. 이동은 4방향의 인접한 격자로만 이동할 수 있습니다. 지도에는 각 위치에 있는 진흙의 양이 주어집니다.
몸의 더러운 정도는 정수형 숫자로, 지나가는 진흙의 양만큼 더러워집니다. 예를 들어, 2, 4, 5 인 진흙을 밟고 탈출한다면 더러운 정도는 
11 이 됩니다. 더러운 정도는 100을 초과하지 않습니다. 즉, 진흙을 아무리 밟아도 100을 초과하지 않습니다. 예를 들어 더러움이 
98인 상태에서 8을 밟더라도 더러움은 100이 됩니다.


입력 조건

첫 번째 라인에 격자의 크기 N 이 주어집니다. (1 <= N <= 10)
두 번째 라인부터 N 개의 라인에 진흙탕 지도가 주어집니다. 각 진흙 양은 0 또는 1자리 양의 정수로 주어집니다.
단, 시작 위치와 탈출구는 진흙이 없습니다. 즉, 0으로만 주어집니다.


출력 형식

최소한으로 몸을 더럽히고 탈출 했을 때 더러운 정도를 출력하세요.

예1 - 입력)
5
10000
09999
02010
99990
01010


예1 - 출력) S 자 모양으로 탈출하는 것이 최적입니다.
6


예2 - 입력)
5
22220
29999
22220
99990
01010


예2 - 출력) 예1 과 유사하지만 마지막에 9를 밟고 가는 것이 더 좋습니다.
11


예3 - 입력)
8
99999990
99999999
99999999
99999999
99999999
99999999
99999999
09999999


예3 - 출력) 100 미만으로 탈출하기는 불가능합니다.
100

*/


#include<iostream>
using namespace std;

const int MAX=9999;
const int N=5;

//const int path[N][N]={
//	{1,0,0,0,0},
//	{0,9,9,9,9},
//	{0,2,0,1,0},
//	{9,9,9,9,0},
//	{0,1,0,1,0}
//};


const int path[N][N]={
	{2,2,2,2,0},
	{2,9,9,9,9},
	{2,2,2,2,0},
	{9,9,9,9,0},
	{0,1,0,1,0}
};


//const int path[N][N]={
//	{9,9,9,9,9,9,9,0},
//	{9,9,9,9,9,9,9,9},
//	{9,9,9,9,9,9,9,9},
//	{9,9,9,9,9,9,9,9},
//	{9,9,9,9,9,9,9,9},
//	{9,9,9,9,9,9,9,9},
//	{9,9,9,9,9,9,9,9},
//	{0,9,9,9,9,9,9,9}
//};

int values[N][N];
bool visited[N][N];

struct pos{
	int x,y;
	int val;
	public:
		pos(int _x,int _y,int _val=0):x(_x),y(_y),val(_val){}
};

int solv(){
	int x=N-1;
	int y=0;

	for(int i=x;i>=0;--i){
		for(int j=y;j<N;++j){
			int left=j-1 >=0 ? j-1:-1;
			int right=j+1<N?j+1:-1;
			int up=i-1>=0?i-1:-1;
			int down=i+1<N?i+1:-1;

			int min=MAX;
			bool changeCheck=false;

			if(left!=-1&&min>values[i][left]+path[i][j]&&visited[i][left]){
				min=values[i][left]+path[i][j];
				changeCheck=true;
			}
			if(right!=-1&&min>values[i][right]+path[i][j]&&visited[i][right]){
				min=values[i][right]+path[i][j];
				changeCheck=true;
			}
			if(up!=-1&&min>values[up][j]+path[i][j]&&visited[up][j]){
				min=values[up][j]+path[i][j];
				changeCheck=true;
			}
			if(down!=-1&&min>values[down][j]+path[i][j]&&visited[down][j]){
				min=values[down][j]+path[i][j];
				changeCheck=true;
			}
			values[i][j]=min==MAX ? values[i][j]:min;
			visited[i][j]=true;

			if(changeCheck){
				int tmpj;
				for(int ri=i;ri<N;++ri){
					if(ri==i) tmpj=j-1; //current 이전 꺼.
					else tmpj=N-1;

					for(int rj=tmpj;rj>=0;--rj){
						int left=rj-1 >=0 ? rj-1:-1;
						int right=rj+1<N?rj+1:-1;
						int up=ri-1>=0?ri-1:-1;
						int down=ri+1<N?ri+1:-1;
						int min=MAX;

						if(ri==x && rj==y) break; //출발점.

						if(left!=-1&&min>values[ri][left]+path[ri][rj]&&visited[ri][left]) min=values[ri][left]+path[ri][rj];
						if(right!=-1&&min>values[ri][right]+path[ri][rj]&&visited[ri][right]) min=values[ri][right]+path[ri][rj];
						if(up!=-1&&min>values[up][rj]+path[ri][rj]&&visited[up][rj]) min=values[up][rj]+path[ri][rj];
						if(down!=-1&&min>values[down][rj]+path[ri][rj]&&visited[down][rj]) min=values[down][rj]+path[ri][rj];
						values[ri][rj]=min==MAX ? values[ri][rj]:min;
					}
				}
			}
		}
	}

	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j) cout<<values[i][j]<<"\t";
		cout<<endl;
	}
	return values[0][N-1]>100 ? 100:values[0][N-1];
}



int main(){
	for(int i=0;i<N;++i)for(int j=0;j<N;++j){values[i][j]=0;visited[i][j]=false;}
	cout<<solv()<<endl;
	return 0;
}
