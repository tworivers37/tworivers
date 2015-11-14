#include "common.h"
#include "AVLRebalance.h"

int GetHeight(BTreeNode *bst){
	int leftHeight;
	int rightHeight;
	if(bst==NULL) return 0;
	leftHeight=GetHeight(GetLeftSubTree(bst)); //왼쪽 서브트리 높이
	rightHeight=GetHeight(GetRightSubTree(bst)); //오른쪽 서브트리 높이
	
	//큰 값의 높이 반환. 낮은 높이의 값은 버림.
	if(leftHeight > rightHeight) return leftHeight+1;
	else return rightHeight+1;
}

int GetHeightDiff(BTreeNode *bst){
	int leftHeight;
	int rightHeight;
	if(bst==NULL) return 0;
	leftHeight=GetHeight(GetLeftSubTree(bst));
	rightHeight=GetHeight(GetRightSubTree(bst));
	return leftHeight-rightHeight;
}

BTreeNode * RotateLL(BTreeNode *bst){
	BTreeNode *pNode;
	BTreeNode *cNode;
	pNode=bst;
	cNode=GetLeftSubTree(bst);
	
	//LL
	ChangeLeftSubTree(pNode,GetRightSubTree(cNode));
	ChangeRightSubTree(cNode,pNode);
	
	return cNode; //root node
}

BTreeNode *RotateRR(BTreeNode *bst){
	BTreeNode *pNode;
	BTreeNode *cNode;
	pNode=bst;
	cNode=GetRightSubTree(bst);

	//RR
	ChangeRightSubTree(pNode,GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode,pNode);
	
	return cNode; //root node
}

//RR -> LL
BTreeNode *RotateLR(BTreeNode *bst){
	BTreeNode *pNode;
	BTreeNode *cNode;
	pNode=bst;
	cNode=GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode,RotateRR(cNode)); //부분 RR
	return RotateLL(pNode); // LL
}

//LL -> RR
BTreeNode *RotateRL(BTreeNode *bst){
	BTreeNode *pNode;
	BTreeNode *cNode;
	pNode=bst;
	cNode=GetRightSubTree(bst);

	ChangeRightSubTree(pNode,RotateLL(cNode)); //부분 LL
	return RotateRR(pNode); // RR
}

BTreeNode *Rebalance(BTreeNode **pRoot){
	int diff=GetHeightDiff(*pRoot);

	//차이가 2이상이면 LL or LR
	if(diff>1){
		if(GetHeight(GetLeftSubTree(*pRoot))>0)
			*pRoot=RotateLL(*pRoot);
		else
			*pRoot=RotateLR(*pRoot);
	}
	//차이가 -2이하면 RR or RL
	if(diff<-1){
		if(GetHeight(GetRightSubTree(*pRoot))>0)
			*pRoot=RotateRL(*pRoot);
		else
			*pRoot=RotateRR(*pRoot);
	}
	return *pRoot;
}
