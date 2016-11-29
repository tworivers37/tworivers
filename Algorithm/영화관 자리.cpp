/*
문제 B. 영화관 자리 선택


영화관을 찾은 커플은 항상 붙은 자리를 원하기 마련입니다. 영화관의 좌석 크기와 이미 팔린 자리들의 정보가 주어질 때, 
가능한 모든 좌우로 연결되어 있는 자리의 수를 출력하는 코드를 작성하세요.

입력 조건

문제를 단순화하여 영화관을 정사각형의 격자 모양이고, 각각의 격자 셀에 좌석이 하나씩 있다고 가정합니다.
입력은 첫번째 라인이 격자 한변의 길이(N)이며, 다음 N개의 라인이 좌석의 상태를 의미합니다.
각 라인은 길이 N의 문자열이며, 점(.) 문자는 팔리지 않은 자리, 별(*) 문자는 이미 판매된 자리를 의미합니다.
N의 크기는 다음과 같습니다. 1 <= N <= 1000


출력 형식

가로로 연속된 자리를 할당할 수 있는 가짓수를 출력합니다.

예1 - 입력)
2
..
**


예1 - 출력) 첫번째 행의 두 자리가 비어있는데, 유일하게 가능한 자리이므로 답은 1 입니다.
1


예2 - 입력)
4
..**
.*..
*...
....


예2 - 출력) 첫번째 행에서는 한가지, 3번째 행에서는 두가지가 가능합니다.
7

*/
#include<iostream>
#include<string>

using namespace std;

int main(){
	int n=0;
	const char star='*';
	const char dot='.';
	int nCnt=0;
	bool bCheck=false;
	int delimiterCheck=0;
	char *cinema=NULL;

	cin>>n;
	cinema=new char[n*n+1];

	for(int i=0;i<n*n;i++) cin>>cinema[i];
	cinema[n*n]=0;
	
	for(int i=0;i<n*n;i++){
		if(bCheck && cinema[i]==dot) nCnt++; //이어지는 dot
		if(!bCheck && cinema[i]==dot) bCheck=true; //처음 dot
		if(cinema[i]==star) bCheck=false; //*
		if(i==(delimiterCheck+1)*n-1){ //라인
			bCheck=false;
			delimiterCheck++;
		}
	}
	
	cout<<nCnt<<endl;

	return 0;
}

