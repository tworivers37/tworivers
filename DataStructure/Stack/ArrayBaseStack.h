#ifndef __ARRAY_BASE_STACK_H__
#define __ARRAY_BASE_STACK_H__

#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef int Data;

typedef struct _arrayStack {
	Data stackArr[STACK_LEN];
	int topIndex;
}ArrayStack;

typedef ArrayStack Stack;

void StackABInit(Stack * pStack);
int SABIsEmpty(Stack * pStack);

void SABPush(Stack*pStack,Data data);
Data SABPop(Stack*pStack);
Data SABPeek(Stack*pStack);


#endif