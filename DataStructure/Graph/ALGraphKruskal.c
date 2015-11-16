#include "ALGraphKruskal.h"
#include "common.h"
#include "ArrayBaseStack.h"

int PQWeightComp(Edge e1,Edge e2){
	return e1.weight-e2.weight;
}
int WhoIsPrecede(int data1,int data2){
	return data1-data2;
}

void GraphInitKruskal(ALGraphKruskal *graph,int nv){
	int i;
	graph->numE=0;
	graph->numV=nv;
	graph->list=(List*)malloc(sizeof(List)*graph->numV);
	graph->visit=(int*)malloc(sizeof(int)*graph->numV);
	PQueueInit(&(graph->queue),PQWeightComp);

	for(i=0;i<graph->numV;i++){
		ListDInit(&(graph->list[i]));
		SetSortRule(&(graph->list[i]),WhoIsPrecede);
	}
}

void GraphDestroyKruskal(ALGraphKruskal *graph){
	if(graph->list!=NULL) free(graph->list);
	if(graph->visit!=NULL) free(graph->visit);
}

void AddEdgeKruskal(ALGraphKruskal *graph,int fromV,int toV,int weight){
	Edge edge={fromV,toV,weight};
	LDInsert(&(graph->list[fromV]),toV);
	LDInsert(&(graph->list[toV]),fromV);
	graph->numE+=1;
	PEnqueue(&(graph->queue),edge);
}

void ShowGraphEdgeInfoKruskal(ALGraphKruskal *graph){
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

int VisitVertexKruskal(ALGraphKruskal *graph,int visitV){
	if(graph->visit[visitV]==0){ // 방문 안된 상태
		graph->visit[visitV]=1;
		//printf("%c ",visitV+'A');
		return TRUE; //방문 성공
	}
	return FALSE;// 방문 실패
}

void DFSShowGraphVertexKruskal(ALGraphKruskal *graph,int startV){
	Stack stack;
	int visitV=startV;
	int nextV;
	int visitFlag;

	StackABInit(&stack);
	VisitVertexKruskal(graph,visitV);
	SAPush(&stack,visitV);

	while(LDFirst(&(graph->list[visitV]),&nextV)==TRUE){
		visitFlag=FALSE;
		if(VisitVertexKruskal(graph,nextV)==TRUE){
			SAPush(&stack,nextV);
			visitV=nextV;
			visitFlag=TRUE;
		}
		else{
			while(LDNext(&(graph->list[visitV]),&nextV)==TRUE){
				if(VisitVertexKruskal(graph,nextV)==TRUE){
					SAPush(&stack,nextV);
					visitV=nextV;
					visitFlag=TRUE;
					break;
				}
			}
		}
		if(visitFlag==FALSE){
			if(SABIsEmpty(&stack)==TRUE)break;
			else visitV=SABPop(&stack);
		}
	}
	memset(graph->visit,0,sizeof(int)*graph->numV);
}


void ShowGraphEdgeWeightInfo(ALGraphKruskal *graph){
	PQueue q=graph->queue;
	Edge edge;
	while(!PQIsEmpty(&q)){
		edge=PDequeue(&q);
		printf("%c-%c , weight : %d\n",edge.v1,edge.v2,edge.weight);
	}
}

//방향
void RemoveWayEdge(ALGraphKruskal *graph,int fromV,int toV){
	int edge;
	if(LDFirst(&(graph->list[fromV]),&edge)){
		if(edge==toV){
			LDRemove(&(graph->list[fromV]));
			return;
		}
		else{
			while(LDNext(&(graph->list[fromV]),&edge)){
				if(edge==toV){
					LDRemove(&(graph->list[fromV]));
					return;
				}
			}
		}
	}
}

void RemoveEdge(ALGraphKruskal *graph,int fromV,int toV){
	//양방향으로 삭제
	RemoveWayEdge(graph,fromV,toV);
	RemoveWayEdge(graph,toV,fromV);
	graph->numE--;
}

//삭제된 간선 복구(양방향으로)
void RecoverEdge(ALGraphKruskal *graph,int fromV,int toV,int weight){
	LDInsert(&(graph->list[fromV]),toV);
	LDInsert(&(graph->list[toV]),fromV);
	graph->numE++;
}

int IsConnVertex(ALGraphKruskal *graph,int v1,int v2){
	Stack stack;
	int visitV=v1;
	int nextV;
	int visitFlag;

	StackABInit(&stack);
	VisitVertexKruskal(graph,visitV);
	SAPush(&stack,visitV);

	while(LDFirst(&(graph->list[visitV]),&nextV)==TRUE){
		visitFlag=FALSE;
		if(nextV==v2){
			memset(graph->visit,0,sizeof(int)*graph->numV);
			return TRUE;
		}

		if(VisitVertexKruskal(graph,nextV)==TRUE){
			SAPush(&stack,nextV);
			visitV=nextV;
			visitFlag=TRUE;
		}
		else{
			while(LDNext(&(graph->list[visitV]),&nextV)==TRUE){
				if(nextV==v2){
					memset(graph->visit,0,sizeof(int)*graph->numV);
					return TRUE;
				}
				if(VisitVertexKruskal(graph,nextV)==TRUE){
					SAPush(&stack,nextV);
					visitV=nextV;
					visitFlag=TRUE;
					break;
				}
			}
		}
		if(visitFlag==FALSE){
			if(SABIsEmpty(&stack)) break;
			else visitV=SABPop(&stack);
		}
	}
	memset(graph->visit,0,sizeof(int)*graph->numV);
	return FALSE;
}

void ConKruskalMST(ALGraphKruskal *graph){
	Edge recvEdge[20];
	Edge edge;
	int idx=0,i;
	while(graph->numE+1>graph->numV){
		edge=PDequeue(&(graph->queue));
		RemoveEdge(graph,edge.v1,edge.v2);
		if(!IsConnVertex(graph,edge.v1,edge.v2)){
			RecoverEdge(graph,edge.v1,edge.v2,edge.weight);
			recvEdge[idx++]=edge;
		}
	}

	for(i=0;i<idx;i++) PEnqueue(&(graph->queue),recvEdge[i]);
}