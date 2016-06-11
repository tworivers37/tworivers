#include<iostream>
using namespace std;

//name : 물건이름
//weight : 물건무게
//worth : 물건의 가치
//N : 물건의 수
//M : 배낭의 한계 
int Knapsack_dynamic(char name[],int weight[],int worth[],int N,int M){
	int *cost=new int[M+1];
	int *best=new int[M+1];
	int x;
	for(x=0;x<=M;x++){
		cost[x]=0;
		best[x]=-1;
	}
	
	for(int i=0;i<N;i++){
		for(x=1;x<=M;x++){
			if(x>=weight[i]){
				if(cost[x]<cost[x-weight[i]]+worth[i]){
					cost[x]=cost[x-weight[i]]+worth[i];
					best[x]=i;
				}
			}
		}
	}
	x=M;
	do{
		cout<<name[best[x]]<<endl;
		x -= weight[best[x]];
	} while (x>0 && best[x]>=0);
	cout<<endl;
	int maxWorth=cost[M];
	delete[]cost;
	delete[]best;
	return maxWorth;
}



int main(){
	char name[5]={'a','b','c','d','e'};
	int weight[5]={3,4,7,8,9};
	int worth[5]={4,5,10,11,13};

	cout<<Knapsack_dynamic(name,weight,worth,5,22)<<endl;

	return 0;
}