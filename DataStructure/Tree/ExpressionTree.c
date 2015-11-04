#include "common.h"
#include "ExpressionTree.h"
#include "ListBaseStack.h"

BTreeNode *MakeExpTree(char exp[]){
	Stack stack; //ListBaseStack.h 의 Data 를 typedef struct _bTreeNode* Data 로 변경 필요
	BTreeNode * node;
	int expLen=strlen(exp);
	int i,j=0;
	char tmp;
	int tmpDigit=0;

	LBStackInit(&stack);

	for(i=0;i<expLen;i++){
		node=MakeBTreeNode();

		if(isdigit(exp[i])){
			while(isdigit(tmp=exp[i+(j++)])){
				tmpDigit*=10;
				tmpDigit+=(tmp-'0');
			}
			SetData(node,tmpDigit);
			i+=j-1;
			tmpDigit=j=0;
		}
		else{
			MakeRightSubTree(node,LBSPop(&stack));
			MakeLeftSubTree(node,LBSPop(&stack));
			SetData(node,exp[i]);
			i++; //공백 패스
		}
		LBSPush(&stack,node);
	}
	return LBSPop(&stack);
}

int EvaluateExpTree(BTreeNode *bt){
	int op1,op2;

	if(GetLeftSubTree(bt)==NULL && GetRightSubTree(bt)==NULL)
		return GetData(bt);

	op1=EvaluateExpTree(GetLeftSubTree(bt));
	op2=EvaluateExpTree(GetRightSubTree(bt));

	switch(GetData(bt)){
		case '+':
			return op1+op2;
		case '-':
			return op1-op2;
		case '*':
			return op1*op2;
		case '/':
			return op1/op2;
	}
	return 0;
}

void ShowNodeData(int data){
	switch(data){
		case '+':
		case '*':
		case '/':
		case '-':
			printf("%c ",data);
			break;
		default:
			printf("%d ",data);
	}	
}

void ShowPrefixTypeExp(BTreeNode *bt){
	PreorderTraverse(bt,ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode *bt){

	if(bt==NULL) return;
	if(bt->left!=NULL || bt->right!=NULL) printf("( ");
	ShowInfixTypeExp(bt->left);
	ShowNodeData(bt->data);
	ShowInfixTypeExp(bt->right);
	if(bt->left!=NULL || bt->right!=NULL) printf(" )");
}

void ShowPostfixTypeExp(BTreeNode *bt){
	PostTraverse(bt,ShowNodeData);
}
