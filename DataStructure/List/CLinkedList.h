#ifndef __C_LINKED_LIST_H__
#define __C_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef int Data;
typedef struct _node {
	Data data;
	struct _node * next;
}Node;

typedef struct _CLL {
	Node *tail;
	Node * cur;
	Node *before;
	int numOfData;
}CList;

typedef CList List;

void ListCInit(List *pList);
void LCInsert(List *pList,Data data);
void LCInsertFront(List *pList,Data data);

int LCFirst(List *pList,Data *data);
int LCNext(List *pList,Data *data);
Data LCRemove(List *pList);
int LCCount(List *pList);


#endif