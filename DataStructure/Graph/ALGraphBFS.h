#ifndef __AL_GRAPH_BFS_H__
#define __AL_GRAPH_BFS_H__

#include "DLinkedList.h"
enum { A,B,C,D,E,F,G,H,I,J,K,L,M,N };

typedef struct _alGraph {
	int numV;
	int numE;
	List *list;
	int *visit;
}ALGraphBFS;

void GraphInitBFS(ALGraphBFS *graph);
void GraphDestroyBFS(ALGraphBFS *graph);
void AddEdgeBFS(ALGraphBFS *graph,int from,int to);
void ShowGraphEdgeInfoBFS(ALGraphBFS *graph);
void BFSShowGraphVertex(ALGraphBFS *graph,int startV);

#endif