#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef int LData;

typedef struct __ArrayList {
	LData arr[LIST_LEN];
	int numOfData;
	int curPosition;
}ArrayList;

typedef ArrayList List;

void ArrayListInit(List*pList);
void ArrayLInsert(List * pList,LData data);
int ArrayLFirst(List * pList,LData *pData);
int ArrayLNext(List * pList,LData * pData);
LData ArrayLRemove(List *pList);
int ArrayLCount(List * pList);

#endif