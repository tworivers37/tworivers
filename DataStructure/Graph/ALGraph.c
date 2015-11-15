#include "ALGraph.h"
#include "common.h"
int WhoIsPrecede(int data1,int data2){
	return data1-data2;
}

void GraphInit(ALGraph *graph,int nv){
	int i;
	graph->list=(List*)malloc(sizeof(List)*nv);
	graph->numE=0;
	graph->numV=nv;

	for(i=0;i<nv;i++){
		ListDInit(&(graph->list[i]));
		SetSortRule(&(graph->list[i]),WhoIsPrecede);
	}
}

void GraphDestory(ALGraph*graph){
	if(graph->list!=NULL) free(graph->list);
}

void AddEdge(ALGraph *graph,int from,int to){
	LDInsert(&(graph->list[from]),to);
	LDInsert(&(graph->list[to]),from);
	graph->numE+=1;
}

void ShowGraphEdgeInfo(ALGraph *graph){
	int i,vx;
	for(i=0;i<graph->numV;i++){
		printf("%c 와 연결된 정점 : ",i+65);
		if(LDFirst(&(graph->list[i]),&vx)){
			printf("%c ",vx+65);
			while(LDNext(&(graph->list[i]),&vx))
				printf("%c ",vx+65);
		}
		puts("");
	}
}