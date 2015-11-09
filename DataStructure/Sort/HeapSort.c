#include "HeapSort.h"

void HeapSort(int arr[],int len,PriorityComp pc){
	Heap heap;
	int i;
	HeapInit(&heap,pc);

	//삽입
	for(i=0;i<len;i++) HInsert(&heap,arr[i]);
	//삭제, 나오면서 PriorityComp 에 맞게 정렬되어 나옴.
	for(i=0;i<len;i++) arr[i]=HDelete(&heap);
}