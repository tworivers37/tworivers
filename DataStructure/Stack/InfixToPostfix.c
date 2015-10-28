#include"common.h"
#include"InfixToPostfix.h"
#include"ListBaseStack.h"


int GetOpPrec(char op){
	switch(op){
		case '*':
		case '/':
			return 10;
		case '+':
		case '-':
			return 5;
		case '(':
			return 1;
	}
	return -1;
}


int WhoPrecOp(char op1,char op2){
	
	int opPrec1=GetOpPrec(op1);
	int opPrec2=GetOpPrec(op2);

	if(opPrec1>opPrec2) return 1;
	else if(opPrec1<opPrec2) return -1;
	else return 0;
}

void headSet(Conv *convExp){
	Value *val=(Value*)malloc(sizeof(Value));
	val->digit=NULL;
	val->operator=(char*)malloc(sizeof(char)*2);
	memset(val->operator,0,2);
	val->next=NULL;

	convExp->head=val;
	convExp->cur=convExp->head;
	convExp->num++;
}

void addValue(Conv*convExp){
	Value *val=(Value*)malloc(sizeof(Value));
	val->digit=NULL;
	val->operator=(char*)malloc(sizeof(char)*2);
	memset(val->operator,0,2);
	val->next=NULL;

	convExp->cur->next=val;
	convExp->cur=convExp->cur->next;
	convExp->num++;
}

char* ConvToRPNExp(char exp[]){
	Stack stack;
	int expLen=strlen(exp);
	char *conv=(char*)malloc(sizeof(char)*expLen*2+1);
	Conv convExp;
	Value *print;
	int i,j=0,idx=0;
	char tok,tokTmp,popOp;
	char digitCheck=FALSE;
	char *addStr=(char*)malloc(sizeof(char)*30);
	int tmpDigit=0,convCnt=0;

	memset(conv,0,sizeof(char)*expLen*2+1);
	LBStackInit(&stack);
	convExp.head=convExp.cur=NULL;
	convExp.num=0;
	
	for(i=0;i<expLen;i++){
		if(isdigit(tok=exp[i])){
			while(isdigit(tokTmp=exp[i+(j++)])){
				tmpDigit*=10;
				tmpDigit+=(tokTmp-'0');
			}

			if(convExp.head==NULL) headSet(&convExp);
			else addValue(&convExp);

			convExp.cur->digit=tmpDigit;

			i+=j-2;
			tmpDigit=j=0;
		}
		else{
			switch(tok){
				case '(':
					LBSPush(&stack,tok);
					break;
				case ')':
					while(1){
						popOp=LBSPop(&stack);
						if(popOp=='(') break;
						addValue(&convExp);
						convExp.cur->operator[0]=popOp;
					}
					break;
				case '+':case '-':
				case '*':case '/':
					while(!LBSIsEmpty(&stack) && WhoPrecOp(LBSPeek(&stack),tok) >=0){
						addValue(&convExp);
						convExp.cur->operator[0]=LBSPop(&stack);
					}
					LBSPush(&stack,tok);
					break;
			}
		}
	}
	while(!LBSIsEmpty(&stack)){
		addValue(&convExp);
		convExp.cur->operator[0]=LBSPop(&stack);
	}

	print=convExp.head;

	for(i=0;print!=NULL;i++){
		if(print->operator[0]!=0) strcat(conv,print->operator);
		else{
			itoa(print->digit,addStr,10);
			strcat(conv,addStr);
		}
		strcat(conv," ");
		print=print->next;
	}
	conv[strlen(conv)-1]=0;
	return conv;
}
