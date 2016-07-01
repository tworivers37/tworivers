#include<iostream>
#include<fstream>	
#include<vector>
#include<string>
using namespace std;
/*
n���� �� �������� �ִ�.������ �� �������� ��� �ϳ� �̻��� �ٸ� �������� ���� ��ũ�� �����ϰ� �ִ�. �̶�
������ �������� ���� ��ũ�� �ϳ� �̻� ������ ���� ���� �ִ�. ���� �Ʒ� �׸��� ������ www.com ����������
mmm.net �������� ���� ��ũ�� 2�� �����Ѵ�.
� �������� �湮�� ����ڴ� �� �������� ���Ե� ��ũ�� �߿� �ϳ��� ������ Ȯ���� Ŭ���Ѵ�. ���� ���
www.com�� �湮�� ����ڴ� �� �������� �ִ� 5���� ��ũ�� �� �ϳ��� 1/5�� Ȯ���� Ŭ���Ѵ�. ��� ��������
�־����� Ŭ�� Ƚ�� k�� �־��� �� k�� Ŭ���� �� �� ����ڰ� �� �������� ��ġ�� Ȯ���� ����Ͽ� ����ϴ� ����
�׷��� �ۼ��϶�.
�Է� �ؽ�Ʈ ������ �̸��� input.txt�̸� ����Ʈ�� ��ũ�� ���� ������ ������ ���� �������� �־�����. ù �ٿ���
����Ʈ�� ���� n�� ��ũ�� ���� m�� �־�����. ����Ʈ���� 0������ n-1�������� ������ ǥ���ȴ�. �̾��� m�ٿ�
�� m���� ��ũ�� ���� ������ �� �ٿ� �ϳ��� �־�����. �� ��ũ�� �� ��ũ�� ���Ե� ����ũ�� ��ȣ�� �� ��ũ��
����Ű�� ����Ʈ�� ��ȣ�� �����ȴ�. �� 2���� ������ ǥ���ȴ�. ������ �ٿ��� ��� ����Ʈ�� ��ȣ�� Ŭ�� Ƚ�� k
�� �־�����.

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
0 2 // ������� 0, Ŭ��Ƚ���� k=2

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

	//������ �Է� ������ ��������-------------
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