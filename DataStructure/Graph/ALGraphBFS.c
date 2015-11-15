#include "common.h"
#include "ALGraphBFS.h"
#include "CircularQueue.h"
int WhoIsPrecede(int data1,int data2){
	return data1-data2;
}
void GraphInitBFS(ALGraphBFS *graph,int nv){
	int i=0;
	graph->numE=0;
	graph->numV=nv;
	graph->list=(List*)malloc(sizeof(List)*graph->numV);
	graph->visit=(int*)malloc(sizeof(int)*graph->numV);
	memset(graph->visit,0,sizeof(int)*graph->numV);

	for(i=0;i<graph->numV;i++){
		ListDInit(graph);
		SetSortRule(&(graph->list),WhoIsPrecede);
	}
}
void GraphDestroyBFS(ALGraphBFS *graph){
	if(graph->list!=NULL) free(graph->list);
	if(graph->visit!=NULL) free(graph->visit);
}
void AddEdgeBFS(ALGraphBFS *graph,int from,int to){
	LDInsert(&(graph->list[from]),to);
	LDInsert(&(graph->list[to]),from);
	graph->numE+=1;
}
void ShowGraphEdgeInfoBFS(ALGraphBFS *graph){
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

int VisitVertex(ALGraphBFS *graph,int visitV){
	if(graph->visit[visitV]==0){ // 방문 안된 상태
		graph->visit[visitV]=1;
		printf("%c ",visitV+'A');
		return TRUE;
	}
	return FALSE;
}
void BFSShowGraphVertex(ALGraphBFS *graph,int startV){
	Queue queue;
	int visitV=startV;
	int nextV;

	CQueueInit(&queue);
	VisitVertex(graph,visitV);
	while(LDFirst(&(graph->list[visitV]),&nextV)==TRUE){
		if(VisitVertex(graph,nextV)==TRUE)
			CEnqueue(&queue,nextV);
		while(LDNext(&(graph->list[visitV]),&nextV)==TRUE){
			if(VisitVertex(graph,nextV)==TRUE) CEnqueue(&queue,nextV);
		}
		if(CQIsEmpty(&queue)==TRUE) break;
		else visitV=CDequeue(&queue);
	}
	memset(graph->visit,0,sizeof(int)*graph->numV);
}