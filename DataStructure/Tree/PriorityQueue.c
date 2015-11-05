#include "PriorityQueue.h"

void PQueueInit(PQueue *ppq,PriorityComp pComp){
	HeapInit(ppq,pComp);
}
int PQIsEmpty(PQueue *ppq){
	return HIsEmpty(ppq);
}

void PEnqueue(PQueue *ppq,PQData data){
	HInsert(ppq,data);
}

PQData PDequeue(PQueue *ppq){
	return HDelete(ppq);
}