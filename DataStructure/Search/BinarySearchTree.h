#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "BinaryTree.h"
#include "common.h"

typedef BTData BSTData;

void BSTMakeAndInit(BTreeNode **pRoot); //초기화 및 생성
BSTData BSTGetNodeData(BTreeNode *bst); //노드 데이터 리턴
BTreeNode* BSTInsert(BTreeNode **pRoot,BSTData data); //데이터 삽입
BTreeNode* BSTSearch(BTreeNode *bst,BSTData target); //데이터 검색
BTreeNode* BSTRemove(BTreeNode** pRoot,BSTData target); //노드 제거
void BSTShowAll(BTreeNode *bst); //데이터 출력

#endif