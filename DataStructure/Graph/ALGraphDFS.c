#include "ALGraphDFS.h"
#include "ArrayBaseStack.h"
#include "common.h"
int WhoIsPrecede(int data1,int data2){
	return data1-data2;
}

void GraphInitDFS(ALGraphDFS *graph,int nv){
	int i;
	graph->list=(List*)malloc(sizeof(List)*nv);
	graph->numE=0;
	graph->numV=nv;
	graph->visit=(int *)malloc(sizeof(int)*graph->numV);
	memset(graph->visit,0,sizeof(int)*graph->numV);

	for(i=0;i<nv;i++){
		ListDInit(&(graph->list[i]));
		SetSortRule(&(graph->list[i]),WhoIsPrecede);
	}

}

void GraphDestoryDFS(ALGraphDFS*graph){
	if(graph->list!=NULL) free(graph->list);
	if(graph->visit!=NULL)free(graph->visit);
}

void AddEdgeDFS(ALGraphDFS *graph,int from,int to){
	LDInsert(&(graph->list[from]),to);
	LDInsert(&(graph->list[to]),from);
	graph->numE+=1;
}

void ShowGraphEdgeInfoDFS(ALGraphDFS *graph){
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

int VisitVertex(ALGraphDFS *graph,int visitV){
	if(graph->visit[visitV]==0){ // 방문 안된 상태
		graph->visit[visitV]=1;
		printf("%c ",visitV+'A');
		return TRUE;
	}
	return FALSE;
}

void DFSShowGraphVertex(ALGraphDFS*graph,int startV){
	Stack stack;
	int visitV=startV;
	int nextV;

	StackInit(&stack);
	VisitVertex(graph,visitV);
	SAPush(&stack,visitV);

	while(LDFirst(&(graph->list[visitV]),&nextV)==TRUE){
		int visitFlag=FALSE;
		if(VisitVertex(graph,nextV)==TRUE){
			SAPush(&stack,visitV);
			visitV=nextV;
			visitFlag=TRUE;
		}
		else{
			while(LDNext(&(graph->list[visitV]),&nextV)==TRUE){
				if(VisitVertex(graph,nextV)==TRUE){
					SAPush(&stack,visitV);
					visitV=nextV;
					visitFlag=TRUE;
					break;
				}
			}
		}
		if(visitFlag==FALSE){
			if(SABIsEmpty(&stack)==TRUE) break;
			else visitV=SABPop(&stack);
		}
	}
	memset(graph->visit,0,sizeof(int)*graph->numV);
}