#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef int LData;

typedef struct _node {
	LData data;
	struct _node *next;
}Node;
typedef struct _linkedList {
	Node*head;
	Node*cur;
	Node*before;
	int numOfData;
	int(*comp)(LData d1,LData d2);
}LinkedList;

typedef LinkedList List;
void ListDInit(List * pList);
void LDInsert(List *pList,LData data);
int LDFirst(List *pList,LData *pData);
int LDNext(List *pList,LData *pData);
LData LDRemove(List *pList);
int LDCount(List *pList);
void SetSortRule(List *pList,int(*comp)(LData d1,LData d2));


#endif 