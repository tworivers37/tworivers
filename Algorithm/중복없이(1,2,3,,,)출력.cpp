/*
중복없이
{1,2,3....}

*/
#include <cstdio>
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

const int n=3;
bool visited[n];

void _func(string p,int c){
	if(c==0){
		//for(int i=1;i<p.length();i+=2) p.insert(i," ");
		//p.insert(p.length()," ");
		cout<<p<<endl;
		return ;
	}
	
	for(int i=0;i<n;++i){
		if(!visited[i]){
			stringstream s;
			s<<i+1;
			p+=s.str();
			visited[i]=true;
			_func(p,c-1);
			p.erase(p.length()-1,1);
			visited[i]=false;
		}
	}
}

int main(){
		_func("",n);
    return 0;
}
