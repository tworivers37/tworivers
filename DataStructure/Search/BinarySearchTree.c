#include "BinarySearchTree.h"
#include "AVLRebalance.h"
void BSTMakeAndInit(BTreeNode **pRoot){
	*pRoot=NULL;
}
BSTData BSTGetNodeData(BTreeNode *bst){
	return GetData(bst);
}
BTreeNode* BSTInsert(BTreeNode **pRoot,BSTData data){
	//BTreeNode *pNode=NULL;
	//BTreeNode *cNode=*pRoot;
	//BTreeNode *nNode=NULL;

	////위치 찾기
	//while(cNode!=NULL){
	//	if(data==GetData(cNode)) return;
	//	pNode=cNode;
	//	if(GetData(cNode)<data) cNode=GetRightSubTree(cNode);
	//	else cNode=GetLeftSubTree(cNode);
	//}
	//
	//nNode=MakeBTreeNode();
	//SetData(nNode,data);

	//if(pNode!=NULL){ //삽입 노드가 루트노드가 아닌 경우
	//	if(GetData(pNode)<data) MakeRightSubTree(pNode,nNode);
	//	else MakeLeftSubTree(pNode,nNode);
	//}
	//else //삽입 되는 노드가 루트 노드가 되는 경우
	//	*pRoot=nNode;

	if(*pRoot==NULL){
		*pRoot=MakeBTreeNode();
		SetData(*pRoot,data);
	}
	else if(GetData(*pRoot)>data){
		BSTInsert(&((*pRoot)->left),data);
		*pRoot=Rebalance(pRoot);
	}
	else if(GetData(*pRoot)<data){
		BSTInsert(&((*pRoot)->right),data);
		*pRoot=Rebalance(pRoot);
	}
	else
		return NULL; //키(data) 중복

	return *pRoot;
}
BTreeNode *BSTSearch(BTreeNode *bst,BSTData target){
	BTreeNode *cNode=bst;
	BSTData cData;

	while(cNode!=NULL){
		cData=GetData(cNode);
		if(target==cData) return cNode;
		else if(target<cData) cNode=GetLeftSubTree(cNode);
		else cNode=GetRightSubTree(cNode);
	}
	return NULL;
}
BTreeNode* BSTRemove(BTreeNode** pRoot,BSTData target){
	BTreeNode *pVRoot=MakeBTreeNode();
	BTreeNode *pNode=pVRoot;
	BTreeNode *cNode=*pRoot;
	BTreeNode *dNode,*dcNode,*mNode,*mpNode;
	BSTData delData;

	//가상 노드의 오른쪽 자식이 루트노드
	ChangeRightSubTree(pVRoot,*pRoot);

	//삭제 대상 검색
	while(cNode!=NULL && GetData(cNode)!=target){
		pNode=cNode;
		if(target<GetData(cNode)) cNode=GetLeftSubTree(cNode);
		else cNode=GetRightSubTree(cNode);
	}

	if(cNode==NULL) return NULL;
	
	dNode=cNode;

	//단말 노드인 경우
	if(GetLeftSubTree(dNode)==NULL && GetRightSubTree(dNode)==NULL){
		if(GetLeftSubTree(pNode)==dNode) RemoveLeftSubTree(pNode);
		else RemoveRightSubTree(pNode);
	}
	//하나의 자식 노드를 갖는 경우
	else if(GetLeftSubTree(dNode)==NULL || GetRightSubTree(dNode)==NULL){
		if(GetLeftSubTree(dNode)!=NULL) dcNode=GetLeftSubTree(dNode);
		else dcNode=GetRightSubTree(dNode);
		if(GetLeftSubTree(pNode)==dNode) ChangeLeftSubTree(pNode,dcNode);
		else ChangeRightSubTree(pNode,dcNode);
	}
	//두 개의 자식 노드를 갖는 경우
	else{
		//삭제 노드를 대체할 노드는 삭제 노드의 오른쪽 서브트리에서의 가장 작은 값을 가진 노드
		mNode=GetRightSubTree(dNode); //대체노드
		mpNode=dNode;//대체노드의 부모노드
				
		//삭제 대상의 대체 노드를 찾음
		while(GetLeftSubTree(mNode)!=NULL){
			mpNode=mNode;
			mNode=GetLeftSubTree(mNode);
		}
		
		//대체노드에 저장된 값을 삭제할 노드에 저장
		delData=GetData(dNode); //삭제 될 노드 값 백업
		SetData(dNode,GetData(mNode));

		//대체노드의 부모노드와 자식노드를 연결
		if(GetLeftSubTree(mpNode)==mNode) ChangeLeftSubTree(mpNode,GetRightSubTree(mNode));
		else ChangeRightSubTree(mpNode,GetRightSubTree(mNode));
		
		dNode=mNode;
		SetData(dNode,delData);
	}
	//삭제된 노드가 루트노드인 경우	
	if(GetRightSubTree(pVRoot)!=*pRoot) *pRoot=GetRightSubTree(pVRoot);

	free(pVRoot);
	*pRoot=Rebalance(pRoot);
	return dNode;
}

void ShowIntData(int data){
	printf("%d ",data);
}

void BSTShowAll(BTreeNode *bst){
	InorderTraverse(bst,ShowIntData);
}