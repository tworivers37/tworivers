#ifndef __DB_LINKED_LIST_H__
#define __DB_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node {
	Data data;
	struct _node * next;
	struct _node * prev;
}Node;

typedef struct _DLinkedList {
	Node *head;
	Node * cur;
	int numOfData;
}DBLinkedList;

typedef DBLinkedList List;

void ListDBInit(List *pList);
void LDBInsert(List *pList,Data data);

int LDBFirst(List *pList,Data *data);
int LDBNext(List * pList,Data *data);
int LDBPrevious(List *pList,Data *data);
int LDBCount(List *pList);
Data LDBRemove(List *pList);

#endif 