#ifndef __AVL_REBALANCE_H__
#define __AVL_REBALANCE_H__

#include "BinaryTree.h"

int GetHeight(BTreeNode *bst); //높이 
int GetHeightDiff(BTreeNode *bst); //높이 차이

BTreeNode*RotateLL(BTreeNode * bst); //LL
BTreeNode*RotateRR(BTreeNode *bst); //RR
BTreeNode*RotateLR(BTreeNode *bst); //LR
BTreeNode*RotateRL(BTreeNode *bst); //RL

BTreeNode * Rebalance(BTreeNode **pRoot); //균형을 맞춤

#endif