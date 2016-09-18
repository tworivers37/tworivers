/*
미로 찾기
크기가 h*w인 미로가 있다.
이 미로는 길과 벽으로 구성되어 있으며, 길은 ".", 벽은 "#"으로 구성되어 있으며,
시작위치 "S"와 도착위치 "G"가 존재한다.
위에서 제시한 각 정보가 주어질 때, S위치로부터 G위치까지의 최단 거리를 구하
는 프로그램을 작성하시오.

입력
첫 번째 줄에 h와 w가 공백으로 구분되어 입력된다.
(단, h, w는 5 이상 100 이하의 자연수이다.)
두 번째 줄부터 h줄에 걸쳐서 w개로 이루어진 문자열이 입력된다.
문자열은 길은 ".", 벽은 "#", 출발점은 "S", 도착점은 "G"로 표시된다. 그리고 S와
G의 위치는 서로 다르다

출력
출발지로부터 도착지까지의 최단거리를 출력한다.
단, 도달할 수 없는 미로일 경우에는 -1을 출력한다.

입력 예 출력 예
5 5
#S###
#...#
#.#.#
#....
###G#

6
*/

#include<iostream>
#include<queue>
using namespace std;

const int h=5,w=5;
const int sX=0,sY=1;
const int gX=4,gY=3;
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
//# 벽
//. 길
//S 출발점
//G 도착점
char arr[h][w]={
	'#','S','#','#','#',
	'#','.','.','.','#',
	'#','.','#','.','#',
	'#','.','.','.','.',
	'#','#','#','G','#'
};
int visited[h][w]={0,};
struct xy{ int x,y; };
bool check(int x,int y){
	if(x<0 || x>=h || y<0 || y>=w) return false;
	if((arr[x][y]=='.'|| arr[x][y]=='S' || arr[x][y]=='G')
	   && !visited[x][y]) return true;
	else return false;
}

int bfs(int x,int y){
	queue<xy> q;
	q.push(xy{x,y});//S
	visited[x][y]=1;
	while(!q.empty()){
		xy tmp=q.front();q.pop();
		for(int i=0;i<4;i++){
			if(check(tmp.x+dx[i],tmp.y+dy[i])){
				visited[tmp.x+dx[i]][tmp.y+dy[i]]=visited[tmp.x][tmp.y]+1;
				q.push(xy{tmp.x+dx[i],tmp.y+dy[i]});
			}
		}
	}
	return visited[gX][gY];
}

int solv(){
	return bfs(sX,sY);
}

int main(){
	cout<<solv()-1<<endl;

	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout<<visited[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
