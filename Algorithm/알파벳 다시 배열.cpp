/*
문제 A. 알파벳 다시 배열하기


문자열 하나가 주어질 때, 알파벳의 빈도수가 적은 것들이 앞쪽에 오도록 다시 배열 하여 출력하는 코드를 작성하세요. 
빈도수가 같다면 알파벳 순으로 먼저인 문자를 앞쪽에 배치하세요. 

입력 조건

첫 번째 라인에 입력 문자열이 주어집니다.
1 <= 문자열 길이 <= 1,000,000
문자열은 영문 대문자로만 구성됩니다.


출력

변환된 문자열을 출력합니다.

예1 - 입력)

ABABAC

예1 - 출력)

CBBAAA

예2 - 입력)

DONTFORGETTHATYOUARESPECIAL

예2 - 출력)

CDFGHILNPSUYRRAAAEEEOOOTTTT





*/

#include<iostream>
#include<string>

using namespace std;

#define ALPHA_NUM 26

int main(){
	string str;
	int strCnt[ALPHA_NUM]={0};
	string strArr[ALPHA_NUM]={""};
	const char *cstr=NULL;
	string result="";

	int max=0;

	cin>>str;
	cstr=str.c_str();

	for(int i=0;i<str.size();i++) if(max<++strCnt[cstr[i]-'A'])max=strCnt[cstr[i]-'A'];
	
	for(int i=0;i<ALPHA_NUM;i++){
		if(strCnt[i]!=0)
			for(int j=0;j<strCnt[i];j++) strArr[i]+=string(1,'A'+i);
	}
	
	for(int i=0;i<max;i++){
		for(int j=0;j<ALPHA_NUM;j++){
			if(strCnt[j]==i+1)
				result+=strArr[j];
		}
	}
	cout<<result<<endl;
	return 0;
}
