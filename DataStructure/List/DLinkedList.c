#include "common.h"
#include "DLinkedList.h"

void ListDInit(List *pList){
	pList->head=(Node*)malloc(sizeof(Node));
	pList->head->next=NULL;
	pList->comp=NULL;
	pList->numOfData=0;
}

void FDInsert(List *pList,LData data){
	Node * node=(Node*)malloc(sizeof(Node));
	node->data=data;

	node->next=pList->head->next;
	pList->head->next=node;
	(pList->numOfData)++;
}
void SDInsert(List *pList,LData data){
	Node * node=(Node*)malloc(sizeof(Node));
	Node *pred=pList->head;
	node->data=data;
	while(pred->next!=NULL && pList->comp(data,pred->next->data) !=0)
		pred=pred->next;
	node->next=pred->next;
	pred->next=node;
	(pList->numOfData)++;
}
void LDInsert(List *pList,LData data){
	if(pList->comp==NULL)
		FDInsert(pList,data);
	else
		SDInsert(pList,data);
}


int LDFirst(List *pList,LData *pData){
	if(pList->head->next==NULL) return FALSE;

	*pData=pList->head->next->data;
	pList->before=pList;
	pList->cur=pList->head->next;
	return TRUE;
}

int LDNext(List * pList,LData *pData){
	if(pList->cur->next==NULL) return FALSE;
	
	pList->before=pList->cur;
	pList->cur=pList->cur->next;
	*pData=pList->cur->data;
	return TRUE;
}
LData LDRemove(List *pList){
	LData rData=pList->cur->data;
	Node *rNode=pList->cur;

	pList->before->next=pList->cur->next;
	pList->cur=pList->before;

	free(rNode);
	(pList->numOfData)--;
	return rData;
}
int LDCount(List *pList){
	return pList->numOfData;
}

void SetSortRule(List *pList,int(*comp)(LData d1,LData d2)){
	pList->comp=comp;
}



