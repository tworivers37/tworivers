#include<iostream>
#include<queue>
using namespace std;

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

struct xy{
	int x,y;
};

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

bool check(int x,int y){
	//범위
	if(x<0||x>=n||y<0||y>=n) return false;
	//두더지 굴
	if(arr[x][y]==1) return true;
	else return false;
}

void bfs(int x,int y){
	queue<xy> q;
	q.push(xy{x,y});
	arr[x][y]=sizeVal;
	mem[sizeVal]+=1;

	while(!q.empty()){
		xy tmp=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			if(check(tmp.x+dx[i],tmp.y+dy[i])){
				arr[tmp.x+dx[i]][tmp.y+dy[i]]=sizeVal;
				mem[sizeVal]+=1;
				q.push(xy{tmp.x+dx[i],tmp.y+dy[i]});
			}
		}
	}
}

void bfs_solv(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(check(i,j)){
				bfs(i,j);
				sizeVal++;
			}
		}
	}

}


int main(){
	bfs_solv();

	cout<<sizeVal-2<<endl;

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
