#ifndef __DEQUE_H__
#define __DEQUE_H__

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node {
	Data data;
	struct _node *next;
	struct _node *prev;
}Node;

typedef struct _dlDeque {
	Node *head;
	Node *tail;
}DLDeque;

typedef DLDeque Deque;

void DequeInit(Deque *pDeque);
int DQIsEmpty(Deque *pDeque);

void DQAddFirst(Deque *pDeque,Data data);
void DQAddLast(Deque *pDeque,Data data);

Data DQRemoveFirst(Deque*pDeque);
Data DQRemoveLast(Deque*pDeque);

Data DQGetFirst(Deque *pDeque);
Data DQGetLast(Deque *pDeque);

#endif