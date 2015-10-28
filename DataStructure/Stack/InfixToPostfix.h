#ifndef __INFIX_TO_POSTFIX_H__
#define __INFIX_TO_POSTFIX_H__



typedef struct _val {
	char *operator;
	int digit;
	struct _val *next;
}Value;

typedef struct _conv {
	Value* head;
	Value* cur;
	int num;
}Conv;

char* ConvToRPNExp(char exp[]);

#endif