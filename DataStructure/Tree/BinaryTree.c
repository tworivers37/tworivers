#include "common.h"
#include "BinaryTree.h"

BTreeNode* MakeBTreeNode(){
	BTreeNode *node=(BTreeNode*)malloc(sizeof(BTreeNode));
	node->left=NULL;
	node->right=NULL;
	return node;
}

BTData GetData(BTreeNode *bt){
	return bt->data;
}

void SetData(BTreeNode *bt,BTData data){
	bt->data=data;
}

BTreeNode *GetLeftSubTree(BTreeNode *bt){
	return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode *bt){
	return bt->right;
}

void MakeLeftSubTree(BTreeNode *main,BTreeNode *sub){
	if(main->left!=NULL)
		free(main->left);
	main->left=sub;
}

void MakeRightSubTree(BTreeNode *main,BTreeNode *sub){
	if(main->right!=NULL)
		free(main->right);
	main->right=sub;
}

void PreorderTraverse(BTreeNode *bt,VisitFuncPtr action){
	if(bt==NULL) return;
	action(bt->data);
	PreorderTraverse(bt->left,action);
	PreorderTraverse(bt->right,action);
}

void InorderTraverse(BTreeNode *bt,VisitFuncPtr action){
	if(bt==NULL) return;
	InorderTraverse(bt->left,action);
	action(bt->data);
	InorderTraverse(bt->right,action);
}

void PostTraverse(BTreeNode *bt,VisitFuncPtr action){
	if(bt==NULL) return;
	PostTraverse(bt->left,action);
	PostTraverse(bt->right,action);
	action(bt->data);
}

void DeleteTree(BTreeNode *bt){
	if(bt==NULL) return;
	DeleteTree(bt->left);
	DeleteTree(bt->right);
	printf("Delete Node Data : %d\n",bt->data);
	free(bt);
}

BTreeNode *RemoveLeftSubTree(BTreeNode *bt){
	BTreeNode *dNode;
	if(bt!=NULL){
		dNode=bt->left;
		bt->left=NULL;
	}
	return dNode;
}

BTreeNode * RemoveRightSubTree(BTreeNode *bt){
	BTreeNode *dNode;
	if(bt!=NULL){
		dNode=bt->right;
		bt->right=NULL;
	}
	return dNode;
}

void ChangeLeftSubTree(BTreeNode *main,BTreeNode *sub){
	main->left=sub;
}

void ChangeRightSubTree(BTreeNode *main,BTreeNode *sub){
	main->right=sub;
}
