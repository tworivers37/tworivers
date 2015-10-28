#include "common.h"
#include "Deque.h"

void DequeInit(Deque *pDeque){
	pDeque->head=NULL;
	pDeque->tail=NULL;
}

int DQIsEmpty(Deque *pDeque){
	if(pDeque->head==NULL) return TRUE;
	else return FALSE;
}

void DQAddFirst(Deque *pDeque,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;
	node->next=pDeque->head;
	
	if(DQIsEmpty(pDeque))
		pDeque->tail=node;
	else
		pDeque->head->prev=node;

	node->prev=NULL;
	pDeque->head=node;
}

void DQAddLast(Deque*pDeque,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;
	node->prev=pDeque->tail;

	if(DQIsEmpty(pDeque))
		pDeque->head=node;
	else
		pDeque->tail->next=node;

	pDeque->tail=node;
	node->next=NULL;
}

Data DQRemoveFirst(Deque*pDeque){
	Node *rNode=NULL;
	Data rData;

	if(DQIsEmpty(pDeque)){
		printf("Queue Memory Error \n");
		exit(-1);
	}

	rNode=pDeque->head;
	rData=pDeque->head->data;
	pDeque->head=pDeque->head->next;

	if(pDeque->head==NULL)
		pDeque->tail=NULL;
	else
		pDeque->head->prev=NULL;
	free(rNode);
	return rData;
}

Data DQRemoveLast(Deque *pDeque){
	Node *rNode=NULL;
	Data rData;

	if(DQIsEmpty(pDeque)){
		printf("Queue Memory Error \n");
		exit(-1);
	}

	rNode=pDeque->tail;
	rData=pDeque->tail->data;
	pDeque->tail=pDeque->tail->prev;

	if(pDeque->tail==NULL)
		pDeque->head=NULL;
	else
		pDeque->tail->next=NULL;
	free(rNode);
	return rData;
}

Data DQGetFirst(Deque *pDeque){
	if(DQIsEmpty(pDeque)){
		printf("Queue Memory Error \n");
		exit(-1);
	}
	return pDeque->head->data;
}

Data DQGetLast(Deque *pDeque){
	if(DQIsEmpty(pDeque)){
		printf("Queue Memory Error \n");
		exit(-1);
	}
	return pDeque->tail->data;
}