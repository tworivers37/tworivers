#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "Heap.h"

typedef Heap PQueue;
typedef HData PQData;

void PQueueInit(PQueue *ppq,PriorityComp pComp);
int PQIsEmpty(PQueue *ppq);

void PEnqueue(PQueue *ppq,PQData data);
PQData PDequeue(PQueue *ppq);

#endif