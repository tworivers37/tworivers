#include "common.h"
#include "BinaryTree.h"

BTreeNode* makeBTreeNode(){
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


