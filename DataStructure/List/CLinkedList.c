#include "common.h"
#include "CLinkedList.h"

void ListCInit(List *pList){
	pList->numOfData=0;
	pList->tail=NULL;
	pList->cur=NULL;
	pList->before=NULL;
}

void LCInsert(List *pList,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;

	if(pList->tail==NULL){
		pList->tail=node;
		node->next=node;
	}
	else{
		node->next=pList->tail->next;
		pList->tail->next=node;
	}
	
	(pList->numOfData)++;
}

void LCInsertFront(List*pList,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;

	if(pList->tail==NULL){
		pList->tail=node;
		node->next=node;
	}
	else{
		node->next=pList->tail->next;
		pList->tail->next=node;
		pList->tail=node; //
	}
	(pList->numOfData)++;
}

int LCFirst(List *pList,Data *data){
	if(pList->tail!=NULL){
		pList->before=pList->tail;
		pList->cur=pList->tail->next;
		*data=pList->cur->data;
		return TRUE;
	}
	return FALSE;
}

int LCNext(List *pList,Data *data){
	if(pList->tail==NULL)return FALSE;
	pList->before=pList->cur;
	pList->cur=pList->cur->next;
	*data=pList->cur->data;
	return TRUE;
}

Data LCRemove(List *pList){
	Data rData=pList->cur->data;
	List *rList=pList->cur;

	
	if(rList==pList->tail){
		if(pList->tail==pList->tail->next)
			pList->tail=NULL;
		else 
			pList->tail=pList->before;
	}

	pList->before->next=pList->cur->next;
	pList->cur=pList->before;

	free(rList);
	(pList->numOfData)--;
	return rData;
}

int LCCount(List *pList){
	return pList->numOfData;
}
