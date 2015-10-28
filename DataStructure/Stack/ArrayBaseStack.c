#include "common.h"
#include "ArrayBaseStack.h"

void StackABInit(Stack*pStack){
	pStack->topIndex=-1;
}
int SABIsEmpty(Stack*pStack){
	if(pStack->topIndex==-1) return TRUE;
	else return FALSE;
}
void SABPush(Stack*pStack,Data data){
	if(pStack->topIndex==STACK_LEN-1){
		printf("STACK FULL \n");
		return;
	}
	pStack->stackArr[++(pStack->topIndex)]=data;
}
Data SABPop(Stack*pStack){

	if(SABIsEmpty(pStack)){
		printf("STACK EMPTY\n");
		exit(-1);
	}

	return pStack->stackArr[(pStack->topIndex)--];
}
Data SABPeek(Stack*pStack){
	if(SABIsEmpty(pStack)){
		printf("STACK EMPTY\n");
		exit(-1);
	}
	return pStack->stackArr[pStack->topIndex];
}


