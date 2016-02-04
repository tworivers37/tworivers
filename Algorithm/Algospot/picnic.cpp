#include<iostream>
#include<cstring>
using namespace std;

int countPair(bool[]);

int testCase;
int sCount; //student
int fCount; //pair
bool areFriends[10][10];

int main(){
	int a,b;
	bool taken[10];

	cin>>testCase;

	for(int i=0;i<testCase;i++){
		cin>>sCount>>fCount;
		memset(areFriends,0,sizeof(areFriends));

		for(int j=0;j<fCount;j++){
			cin>>a>>b;
			areFriends[a][b]=areFriends[b][a]=true;
		}
		memset(taken,0,sizeof(taken));
		cout<<countPair(taken)<<endl;
	}
	return 0;
}

int countPair(bool taken[]){
	int first=-1;
	int ret=0;
	for(int i=0;i<sCount;i++){
		if(!taken[i]){
			first=i;
			break;
		}
	}
	if(first==-1) return 1;
	for(int i=first+1;i<sCount;i++){
		if(!taken[i] && areFriends[first][i]){
			taken[i]=taken[first]=true;
			ret+=countPair(taken);
			taken[i]=taken[first]=false;
		}
	}
	return ret;
}