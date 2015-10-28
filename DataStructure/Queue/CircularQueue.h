#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#define TRUE 1
#define FALSE 0

#define QUEUE_LEN 100
typedef int Data;

typedef struct _cQueue {
	int front;
	int rear;
	Data queArr[QUEUE_LEN];
}CQueue;

typedef CQueue Queue;

void CQueueInit(Queue * pQueue);
int CQIsEmpty(Queue * pQueue);

void CEnqueue(Queue *pQueue,Data data);
Data CDequeue(Queue *pQueue);
Data CQPeek(Queue *pQueue);

#endif