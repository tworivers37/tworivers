#ifndef __AL_GRAPH_H__
#define __AL_GRAPH_H__

#include "DLinkedList.h"

enum {A,B,C,D,E,F,G,H,I,J,K,L,M,N};

typedef struct _alGraph {
	int numV;
	int numE;
	List *list;
}ALGraph;

void GraphInit(ALGraph *graph,int nv);
void GraphDestroy(ALGraph *graph);
void AddEdge(ALGraph *graph,int from,int to);
void ShowGraphEdgeInfo(ALGraph *graph);

#endif