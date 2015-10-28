#ifndef __LIST_BASE_QUEUE_H__
#define __LIST_BASE_QUEUE_H__

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node {
	Data data;
	struct _node *next;
}Node;

typedef struct _lQueue {
	Node *front;
	Node *rear;
}LQueue;

typedef LQueue Queue;

void LBQueueInit(Queue *pQueue);
int LBQueueIsEmpty(Queue *pQueue);

void LBEnqueue(Queue *pQueue,Data data);
Data LBDequeue(Queue *pQueue);
Data LBQPeek(Queue *pQueue);

#endif