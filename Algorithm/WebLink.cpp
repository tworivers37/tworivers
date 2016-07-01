#include<iostream>
#include<fstream>	
#include<vector>
#include<string>
using namespace std;
/*
n개의 웹 페이지가 있다.각각의 웹 페이지는 적어도 하나 이상의 다른 페이지에 대한 링크를 포함하고 있다. 이때
동일한 페이지에 대한 링크를 하나 이상 가지고 있을 수도 있다. 가령 아래 그림의 예에서 www.com 페이지에는
mmm.net 페이지에 대한 링크가 2개 존재한다.
어떤 페이지를 방문한 사용자는 그 페이지에 포함된 링크들 중에 하나를 동일한 확률로 클릭한다. 예를 들어
www.com을 방문한 사용자는 그 페이지에 있는 5개의 링크들 중 하나를 1/5의 확률로 클릭한다. 출발 페이지가
주어지고 클릭 횟수 k가 주어질 때 k번 클릭을 한 후 사용자가 각 페이지에 위치할 확률을 계산하여 출력하는 프로
그램을 작성하라.
입력 텍스트 파일의 이름은 input.txt이며 사이트와 링크에 대한 정보가 다음과 같은 형식으로 주어진다. 첫 줄에는
사이트의 개수 n과 링크의 개수 m이 주어진다. 사이트들은 0번에서 n-1번까지의 정수로 표현된다. 이어진 m줄에
는 m개의 링크에 대한 정보가 한 줄에 하나씩 주어진다. 각 링크는 그 링크가 포함된 사이크의 번호와 그 링크가
가리키는 사이트의 번호로 구성된다. 즉 2개의 정수로 표현된다. 마지막 줄에는 출발 사이트의 번호와 클릭 횟수 k
가 주어진다.

-sample input-

5 10 // n=5, m=10
0 1
1 2
1 2
1 3
1 3
1 4
2 3
3 0
4 0
4 2
0 2 // 출발점은 0, 클릭횟수는 k=2

-output-

0.0
0.0
0.4
0.4
0.2

*/
vector<vector<int>> vec;
double *result;

void WebLink(int start,int clickCnt,double val){
	if (clickCnt==0) return;
	else{
		int size=vec[start].size();
		double value=1.0/size*val;
		for (int i=0;i<vec[start].size();i++){
			WebLink(vec[start][i],clickCnt-1,value);
			if(clickCnt-1==0) result[vec[start][i]]+=value;
		}
	}
}

int main(){
	ifstream inFile("web.txt");
	char line[15];
	int siteCount=0,linkCount=0;
	string tmp;

	//파일의 입력 데이터 가져오기-------------
	inFile.getline(line,10);
	for (int i=0;i<10;i++){
		if (line[i]!=' ') tmp+=line[i];
		else{
			siteCount=stoi(tmp);
			tmp="";
		}
	}
	linkCount=stoi(tmp);

	for (int i=0;i<siteCount;i++){
		vector<int> elem;
		vec.push_back(elem);
	}

	int idx=0;
	int last=0;
	int start,clickCnt;
	while (last++<linkCount/*!inFile.eof()*/){
		inFile.getline(line,10);
		tmp="";
		for (int i=0;i<10;i++){
			if (line[i]!=' ') tmp+=line[i];
			else{
				idx=stoi(tmp);
				tmp="";
			}
		}
		vec[idx].push_back(stoi(tmp));
	}

	inFile.getline(line,10);
	tmp="";
	for (int i=0;i<10;i++){
		if (line[i]!=' ') tmp+=line[i];
		else{
			start=stoi(tmp);
			tmp="";
		}
	}
	clickCnt=stoi(tmp);
	inFile.close();
	//------------------------

	result=new double[siteCount];
	for (int i=0;i<siteCount;i++) result[i]=0;

	WebLink(start,clickCnt,1);

	for (int i=0;i<siteCount;i++)cout<<result[i]<<endl;
	cout<<endl;

	return 0;
}