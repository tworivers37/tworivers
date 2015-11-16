#ifndef __AL_GRAPH_KRUSKAL_H__
#define __AL_GRAPH_KRUSKAL_H__

#include "DLinkedList.h"
#include "PriorityQueue.h"
#include "ALEdge.h"

enum { A,B,C,D,E,F,G,H,I,J,K,L,M,N };

typedef struct _alGraph {
	int numV;
	int numE;
	List *list;
	int *visit;
	PQueue queue;
}ALGraphKruskal;


void GraphInitKruskal(ALGraphKruskal *graph,int nv);
void GraphDestroyKruskal(ALGraphKruskal *graph);
void AddEdgeKruskal(ALGraphKruskal *graph,int fromV,int toV,int weight);
void ShowGraphEdgeInfoKruskal(ALGraphKruskal *graph);
void DFSShowGraphVertexKruskal(ALGraphKruskal *graph,int startV);
void ConKruskalMST(ALGraphKruskal *graph);
void ShowGraphEdgeWeightInfo(ALGraphKruskal *graph);

#endif