/*
대학 연구소에서 ACGT 염기서열 나타내는 Genetic sequence in digital format으로 저장된 문자열 전달 받았고, 이 문자열로부터 특이
codon의 시작 위치를 확인해야하는 상황이다. 전달받은 문자열에 포함되어 있는 특이 codon의 시작 위치를 출력할 수 있는 findCodon 함수를
작성하시오.

"GCCGCCG" 인 경우 첫 번째 "GCCG"만 인정되며 두 번째 패턴은 무시한다.

[ACGT 입력 샘플]
ACCGGCCGAGACAGCGAGCATATGCCGCCGAGACAGGCCGGACCGGCCGAGA

[codon 입력 샘플]
GCCG

[출력 샘플]
4
23
36
45

*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;
vector<int> getPi(string p);
vector<int> kmp(string s,string p);

int main(){
	string s="ACCGGCCGAGACAGCGAGCATATGCCGCCGAGACAGGCCGGACCGGCCGAGA";
	string p="GCCG";

	vector<int> aa=kmp(s,p);
	for(int i=0;i<aa.size();++i) cout<<aa[i]<<" ";
	cout<<endl;

	return 0;
}
vector<int> getPi(string p){
	int m = (int)p.size(), j=0;
	vector<int> pi(m, 0);
	for(int i = 1; i< m ; i++){
		while(j > 0 && p[i] !=  p[j])
			j = pi[j-1];
		if(p[i] == p[j])
			pi[i] = ++j;
	}
	return pi;
}
vector<int> kmp(string s,string p){
	vector<int> ans;
	vector<int> pi = getPi(p);
	int n = (int)s.size(), m = (int)p.size(), j =0;
	for(int i = 0 ; i < n ; i++){
		while(j>0 && s[i] != p[j]) j = pi[j-1];
		if(s[i] == p[j]){
			if(j==m-1){
				ans.push_back(i-m+1);
				//"GCCGCCG" 인 경우 첫 번째 "GCCG"만 인정되며 두 번째 패턴은 무시 안할 때
				//j = pi[j];
				
				//"GCCGCCG" 인 경우 첫 번째 "GCCG"만 인정되며 두 번째 패턴은 무시 할 때
				j=0;
			}
			else j++;
		}
	}
	return ans;
}
