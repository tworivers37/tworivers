/*
LCS는 2개의 String을 비교하여 최장 공통 부분 문자열을 구함. 
substring을 구하는 것과 다르게 연속적이지 않아도 되기 때문에 같은 길이의 다른 해가 나타날 수 있음.
*/

#include<iostream>
#include<vector>
int main(){
	std::vector<std::vector<int> > table;
	std::string str1="abcdefg";
	std::string str2="abcdeee";
	int max=0;
	table.resize(str1.size()+1);
	for(int i=0;i<str1.size()+1;++i){
		table[i].resize(str2.size()+1);
		table[i].assign(str2.size()+1,0);
	}
	
	for(int i=1;i<str1.size()+1;++i){
		for(int j=1;j<str2.size()+1;++j){
			if(str1[i-1]==str2[j-1]){
				max=table[i-1][j-1]+1;
				table[i][j]=max;
			}
			else table[i][j]= table[i-1][j] > table[i][j-1] ? table[i-1][j] : table[i][j-1];
		}
	}
	
	std::cout<<max<<std::endl;
	for(int i=0;i<str1.size()+1;++i){
		for(int j=0;j<str2.size()+1;++j) std::cout<<table[i][j]<<" ";
		std::cout<<std::endl;
	}
	
	return 0;
}
