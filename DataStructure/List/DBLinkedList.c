#include "common.h"
#include "DBLinkedList.h"

void ListDBInit(List *pList){
	pList->cur=NULL;
	pList->head=NULL;
	pList->numOfData=0;
}

void LDBInsert(List *pList,Data data){
	Node *node=(Node *)malloc(sizeof(Node));
	node->data=data;

	if(pList->head==NULL){
		node->next=node;
		node->prev=node;
	}
	else{
		node->next=pList->head;
		node->prev=pList->head->prev;

		pList->head->prev->next=node;
		pList->head->prev=node;
	}
	pList->head=node;
	(pList->numOfData)++;
}

int LDBFirst(List *pList,Data *data){
	if(pList->head==NULL) return FALSE;
	pList->cur=pList->head;
	*data=pList->cur->data;
	return TRUE;
}

int LDBNext(List *pList,Data*data){
	if(pList->cur->next==NULL)return FALSE;
	pList->cur=pList->cur->next;
	*data=pList->cur->data;
	return TRUE;
}

int LDBPrevious(List *pList,Data *data){
	if(pList->cur->prev==NULL) return FALSE;
	pList->cur=pList->cur->prev;
	*data=pList->cur->data;
	return TRUE;
}

int LDBCount(List *pList){
	return pList->numOfData;
}

Data LDBRemove(List *pList){
	Data rData=pList->cur->data;
	Node *rList=pList->cur;
	
	if(rList==pList->head){
		rList->next->prev=rList->prev;
		rList->prev->next=rList->next;
		pList->head=rList->next;
	}
	else if(rList==pList->head->prev){
		rList->prev->next=rList->next;
		rList->next->prev=rList->prev;
	}
	else{
		rList->prev->next=rList->next;
		rList->next->prev=rList->prev;
	}
	free(rList);
	
	return rData;
}
