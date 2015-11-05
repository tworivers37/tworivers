#include "common.h"
#include "Heap.h"

void HeapInit(Heap *heap,PriorityComp pComp){
	heap->numOfData=0;
	heap->comp=pComp;
}

int HIsEmpty(Heap *heap){
	if(heap->numOfData==0) return TRUE;
	else return FALSE;
}

int GetParentIDX(int idx){
	return idx/2;
}

int GetLChildIDX(int idx){
	return idx*2;
}

int GetRChildIDX(int idx){
	return GetLChildIDX(idx)+1;
}

int GetHighPriChildIDX(Heap *heap,int idx){
	if(GetLChildIDX(idx) > heap->numOfData) return 0;// 자식노드 없음.
	else if(GetLChildIDX(idx)==heap->numOfData) return GetLChildIDX(idx); //자식노드 하나 있음(왼쪽).
	else{
		if(heap->comp(heap->heapArr[GetLChildIDX(idx)],heap->heapArr[GetRChildIDX(idx)]) < 0) return GetRChildIDX(idx);
		else return GetLChildIDX(idx);
	}
}

void HInsert(Heap *heap,HData data){
	int idx=heap->numOfData+1;
	while(idx!=1){
		if(heap->comp(data,heap->heapArr[GetParentIDX(idx)])>0){
			heap->heapArr[idx]=heap->heapArr[GetParentIDX(idx)];
			idx=GetParentIDX(idx);
		}
		else break;
	}
	heap->heapArr[idx]=data;
	heap->numOfData+=1;
}

HData HDelete(Heap *heap){
	HData rData=heap->heapArr[1];
	HData lastElem=heap->heapArr[heap->numOfData];

	int parentIdx=1;
	int childIdx;

	while(childIdx=GetHighPriChildIDX(heap,parentIdx)){
		if(heap->comp(lastElem,heap->heapArr[childIdx])>=0)
			break;
		heap->heapArr[parentIdx]=heap->heapArr[childIdx];
		parentIdx=childIdx;
	}
	heap->heapArr[parentIdx]=lastElem;
	heap->numOfData-=1;
	return rData;
}