#include "common.h"
#include "BinaryTree.h"

void print(int data);

void main(){
	BTreeNode *bt1=MakeBTreeNode();
	BTreeNode *bt2=MakeBTreeNode();
	BTreeNode *bt3=MakeBTreeNode();
	BTreeNode *bt4=MakeBTreeNode();
	BTreeNode *bt5=MakeBTreeNode();

	SetData(bt1,1);
	SetData(bt2,10);
	SetData(bt3,100);
	SetData(bt4,1000);
	SetData(bt5,10000);

	MakeLeftSubTree(bt1,bt2);
	MakeRightSubTree(bt1,bt3);
	MakeLeftSubTree(bt2,bt4);
	MakeRightSubTree(bt2,bt5);
	
	PreorderTraverse(bt1,print);
	puts("");
	InorderTraverse(bt1,print);
	puts("");
	PostTraverse(bt1,print);

}

void print(int data){
	printf("DATA = %d\n",data);
}