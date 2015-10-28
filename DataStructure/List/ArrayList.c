#include "common.h"
#include "ArrayList.h"

void ArrayListInit(List*pList){
	pList->curPosition=-1;
	pList->numOfData=0;
}

void ArrayLInsert(List * pList,LData data){
	if(pList->numOfData >= LIST_LEN){
		printf("LIST FULL\n");
		return;
	}
	pList->arr[pList->numOfData++]=data;
}
int ArrayLFirst(List * pList,LData *pData){
	if(pList->numOfData!=0){
		pList->curPosition=0;
		*pData=pList->arr[0];
		return TRUE;
	}
	else return FALSE;
}
int ArrayLNext(List *pList,LData *pData){
	if(pList->curPosition>=0 && pList->curPosition<LIST_LEN){
		pList->curPosition++;
		*pData=pList->arr[pList->curPosition];
		return TRUE;
	}
	else return FALSE;
}
LData ArrayLRemove(List * pList){
	LData rData=pList->arr[pList->curPosition];
	int i=0;
	for(i=pList->curPosition;i<LIST_LEN-(pList->curPosition);i++)
		pList->arr[i]=pList->arr[i+1];
	pList->curPosition--;
	pList->numOfData--;
	return rData;
}
int ArrayLCount(List * pList){
	return pList->numOfData;
}
