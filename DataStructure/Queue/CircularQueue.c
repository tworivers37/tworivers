#include "common.h"
#include "CircularQueue.h"


void CQueueInit(Queue*pQueue){
	pQueue->front=0;
	pQueue->rear=0;
}

int NextPosIdx(int pos){
	if(pos==QUEUE_LEN-1) return 0;
	else return pos+1;
}

int CQIsEmpty(Queue *pQueue){
	if(pQueue->front==pQueue->rear) return TRUE;
	else return FALSE;
}

void CEnqueue(Queue *pQueue,Data data){
	if(NextPosIdx(pQueue->rear)==pQueue->front){
		printf("Queue Memory Error\n");
		exit(-1);
	}
	pQueue->rear=NextPosIdx(pQueue->rear);
	pQueue->queArr[pQueue->rear]=data;
}

Data CDequeue(Queue *pQueue){
	if(CQIsEmpty(pQueue)){
		printf("Queue Memory Error\n");
		exit(-1);
	}
	pQueue->front=NextPosIdx(pQueue->front);
	return pQueue->queArr[pQueue->front];
}

Data CQPeek(Queue *pQueue){
	if(CQIsEmpty(pQueue)){
		printf("Queue Memory Error\n");
		exit(-1);
	}
	return pQueue->queArr[NextPosIdx(pQueue->front)];
}
