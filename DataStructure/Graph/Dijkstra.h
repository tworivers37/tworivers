#ifndef __DIJKSTRA_H__

#include "common.h"
#define INT_MAX 2147483647 //최대 정수
#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 7 //정점 수
#define INF 9999 //연결이 없는 경우

//int weight[MAX_VERTICE][MAX_VERTICE]; //인접 행렬
int distance[MAX_VERTICE]; //시작 정점에서 최단 거리
int found[MAX_VERTICE]; //방문한 정점 true

typedef struct _node {
	int ver;
	struct _node *next;
}Node;

typedef struct _path {
	Node *node;
	Node *tail;
}Path; //Path 배열의 인덱스가 출발점의 목적지

int Choose(int distance[],int n,int found[]); //최단 경로 선택
void ShortestPath(int start,int n,Path *path,int (*weight)[MAX_VERTICE]);

#endif