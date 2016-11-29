/*
문제 C. 휴지 줍기


정원에 있는 휴지들의 좌표들이 주어질 때, 모든 휴지들을 줍고 나갈 수 있는 최적의 경로를 구하는 코드를 작성하세요.
정원은 2차원 좌표로 각 휴지들의 좌표는 모두 정수형으로 주어집니다. 출발점은 (0,0) 이며, 도착점 (10,10) 입니다.
최적의 경로는 이동한 거리의 합이 가장 짧은 경로입니다. 최적인 경로가 여러가지일 경우, 아무 경로나 출력합니다.


입력 조건

첫 번째 라인에 휴지의 개수 N 이 주어집니다.
두 번째 라인부터 N 개의 라인은 각각이 휴지 하나의 좌표입니다. 좌표 X 와 좌표 Y 는 공백으로 구분됩니다. 크기 제한은 다음과 같습니다. 중복된 좌표는 없습니다.
1 <= N <= 10, 정수
0 <= X, Y <= 10, 정수


출력 형식

“(X,Y)” 형식으로 경로의 좌표들을 모두 출력합니다. 거리를 출력할 필요는 없습니다.
좌표 사이는 “ -> “ 로 연결합니다. 

예 - 입력)
3
3 3
7 7
10 0


예 - 출력) 아래 그래프를 참고하세요. 거리는 sqrt(18) + sqrt(58) + sqrt(58) + sqrt(18) = 약 23.717 입니다.
(0,0) -> (3,3) -> (10,0) -> (7,7) -> (10,10)

*/


#include<iostream>
#include<string>
using namespace std;

#define INF 99999

struct coordinate{
	int x,y;
};


double distanceCalc(coordinate s,coordinate d);
void printXY(int x,int y);

int main(){
	int n=0;
	coordinate *xy=NULL;
	double minDistance=INF;
	int x,y;
	int index;
	coordinate source={0,0};

	cin>>n;
	xy=new coordinate[n];

	for(int i=0;i<n;i++) cin>>xy[i].x>>xy[i].y;

	printXY(0,0);
	cout<<"-> ";

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(xy[j].x>=0 && xy[j].y>=0){
				if(minDistance>=distanceCalc(source,xy[j])){
					minDistance=distanceCalc(source,xy[j]);
					x=xy[j].x;
					y=xy[j].y;
					index=j;
				}
			}
		}		
		printXY(x,y);
		cout<<"-> ";
		source={x,y};

		minDistance=INF;
		xy[index].x=xy[index].y=-1;
	}
	printXY(10,10);

	return 0;
}

void printXY(int x,int y){
	cout<<"( "<<x<<" , "<<y<<" ) ";
}

double distanceCalc(coordinate s,coordinate d){
	return sqrt(pow(s.x-d.x,2)+pow(s.y-d.y,2));
}
