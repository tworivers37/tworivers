#include"common.h"
#include"ListBaseStack.h"

void LBStackInit(Stack *pStack){
	pStack->head=NULL;
}

int LBSIsEmpty(Stack *pStack){
	if(pStack->head==NULL) return TRUE;
	else return FALSE;
}

void LBSPush(Stack *pStack,Data data){
	Node *node=(Node*)malloc(sizeof(Node));
	node->data=data;
	node->next=pStack->head;
	pStack->head=node;
}

Data LBSPop(Stack *pStack){
	Data popData=pStack->head->data;
	Node *rNode=pStack->head;

	if(LBSIsEmpty(pStack)){
		printf("STACK EMPTY\n");
		exit(-1);
	}
	
	pStack->head=pStack->head->next;
	free(rNode);
	return popData;
}

Data LBSPeek(Stack *pStack){
	if(LBSIsEmpty(pStack)){
		printf("STACK EMPTY\n");
		exit(-1);
	}
	return pStack->head->data;
}
