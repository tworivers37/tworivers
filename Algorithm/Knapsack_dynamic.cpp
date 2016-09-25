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

	for(int i=0;i<N;i++){	// 각 물건을 추가 할 때마다의 최적을 구함.
							// index 1은 두 번째(0 다음) 이므로 앞에 하나의 물건이 있었을 때의
							// 최적의 값들에 대해 1이 들어갔을 때(물건이 두 가지 일 때)의 최적의 값으로 업데이트함.
		for(x=1;x<=M;x++){	// 가방의 무게 1, 2, 3, 4, ...
							// 가방의 무게에 따른 최적을 구함.
			if(x>=weight[i]){	// 현재 가방의 무게보다 적은 물건만 참.
								// x 라는 가방 무게에 최대로 높은 가치의 값이
								// cost[x]에 들어감.
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
