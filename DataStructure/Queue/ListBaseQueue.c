#include "common.h"
#include "ListBaseQueue.h"

void LBQueueInit(Queue *pQueue){
	pQueue->front=NULL;
	pQueue->rear=NULL;
}

int LBQueueIsEmpty(Queue *pQueue){
	if(pQueue->front==NULL) return TRUE;
	else return FALSE;
}

void LBEnqueue(Queue *pQueue,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;
	node->next=NULL;

	if(LBQueueIsEmpty(pQueue)){
		pQueue->front=node;
		pQueue->rear=node;
	}
	else{
		pQueue->rear->next=node;
		pQueue->rear=node;
	}
}

Data LBDequeue(Queue *pQueue){
	Node *rNode=NULL;
	Data rData;
	if(LBQueueIsEmpty(pQueue)){
		printf("Queue Memory Error\n");
		exit(-1);
	}

	rNode=pQueue->front;
	rData=pQueue->front->data;

	pQueue->front=pQueue->front->next;
	free(rNode);
	return rData;
}

Data LBQPeek(Queue *pQueue){
	if(LBQueueIsEmpty(pQueue)){
		printf("Queue Memory Error\n");
		exit(-1);
	}
	return pQueue->front->data;
}
