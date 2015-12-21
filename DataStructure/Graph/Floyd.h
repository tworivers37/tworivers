#ifndef __FLOYD_H_

#include "Common.h"
#define INT_MAX 2147483647 //최대 정수
#define TRUE 1
#define FALSE 0
#define MAX_VERTICE 7 //정점 수
#define INF 9999 //연결이 없는 경우

typedef struct _node {
	int ver;
	struct _node *next;
}Node;

typedef struct _path {
	Node *node;
	Node *tail;
}Path; //Path 배열의 인덱스가 출발점의 목적지


void Floyd(int n,int(*weight)[MAX_VERTICE],int(*distance)[MAX_VERTICE],Path *path);

#endif