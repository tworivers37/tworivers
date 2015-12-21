#include "Floyd.h"

void Floyd(int n,int (*weight)[MAX_VERTICE],int (*distance)[MAX_VERTICE],Path *path){
	int i,j,k;
	Node *nNode;

	for(i=0; i<n; i++){
		path[i].node=NULL;
		path[i].tail=NULL;

		for(j=0; j<n; j++)
			distance[i][j]=weight[i][j];
	}

	for(k=0; k<n; k++){
		for(i=0; i<n; i++)
			for(j=0; j<n; j++)
			if(distance[i][k]+distance[k][j] < distance[i][j]){
				distance[i][j]=distance[i][k]+distance[k][j];
				//path 
				nNode=(Node*)malloc(sizeof(Node));
				nNode->ver=k;
				nNode->next=NULL;
				if(path[j].node==NULL){
					path[j].node=nNode;
					path[j].tail=nNode;
				}
				else{
					nNode->next=path[j].node;
					path[j].node=nNode;
				}
			}			
	}
}