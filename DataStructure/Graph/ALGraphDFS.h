#ifndef __AL_GRAPH_DFS_H__
#define __AL_GRAPH_DFS_H__

#include "DLinkedList.h"
enum { A,B,C,D,E,F,G,H,I,J,K,L,M,N };

typedef struct _alGraph {
	int numV;
	int numE;
	List *list;
	int *visit;
}ALGraphDFS;

void GraphInitDFS(ALGraphDFS *graph,int nv);
void GraphDestroyDFS(ALGraphDFS *graph);
void AddEdgeDFS(ALGraphDFS *graph,int from,int to);
void ShowGraphEdgeInfoDFS(ALGraphDFS *graph);
void DFSShowGraphVertex(ALGraphDFS*graph,int startV);

#endif