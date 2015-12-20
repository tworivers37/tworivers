#include "Dijkstra.h"

/*
	test main function

	void main(){
		Path path[MAX_VERTICE];
		int i=0;
		Node *p;
		int weight[MAX_VERTICE][MAX_VERTICE]={
			{0,7,INF,INF,3,10,INF},
			{7,0,4,10,2,6,INF},
			{INF,4,0,2,INF,INF,INF},
			{INF,10,2,0,11,9,4},
			{3,2,INF,11,0,INF,5},
			{10,6,INF,9,INF,0,INF},
			{INF,INF,INF,4,5,INF,0}
		};
		ShortestPath(0,MAX_VERTICE,path,weight);

		for(i=0;i<MAX_VERTICE;i++){
			p=path[i].node;
			printf("0 ");
			while(p!=NULL){
				printf("%d ",p->ver);
				p=p->next;
			}
			printf("%d [VAL : %d]\n",i,distance[i]);
		}
	}
*/

int Choose(int distance[],int n,int found[]){
	int i,min,minPosition;
	min=INT_MAX;
	minPosition=-1;
	for(i=0;i<n;i++){
		if(min>distance[i] && !found[i]){
			min=distance[i];
			minPosition=i;
		}
	}
	return minPosition;
}

void ShortestPath(int start,int n,Path *path,int (*weight)[MAX_VERTICE]){
	int i,u,w;
	Node *nNode;

	//√ ±‚»≠
	for(i=0;i<n;i++){
		distance[i]=weight[start][i];
		found[i]=FALSE;
		path[i].node=NULL;
		path[i].tail=NULL;
	}
	found[start]=TRUE;
	distance[start]=0;
	for(i=0;i<n;i++){
		u=Choose(distance,n,found);
		found[u]=TRUE;
		for(w=0;w<n;w++){
			if(!found[w]){
				if(distance[u]+weight[u][w]<distance[w]){
					distance[w]=distance[u]+weight[u][w];
					//path 
					nNode=(Node*)malloc(sizeof(Node));
					nNode->ver=u;
					nNode->next=NULL;
					if(path[w].node==NULL){
						path[w].node=nNode;
						path[w].tail=nNode;
					}
					else{
						nNode->next=path[w].node;
						path[w].node=nNode;
					}
				}
			}
		}
	}
}

