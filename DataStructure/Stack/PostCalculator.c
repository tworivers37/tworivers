#include "common.h"
#include "PostCalculator.h"
#include "ListBaseStack.h"


int EvalRPNExp(char exp[]){

	Stack stack;
	int expLen=strlen(exp);
	int i,j=0;
	char tok,tokTmp;
	int tmpDigit=0,op1,op2;

	LBStackInit(&stack);

	for(i=0;i<expLen;i++){
		if(isdigit(tok=exp[i])){
			while(isdigit(tokTmp=exp[i+(j++)])){
				tmpDigit*=10;
				tmpDigit+=(tokTmp-'0');
			}
			LBSPush(&stack,tmpDigit);

			i+=j-1;
			tmpDigit=j=0;
			
		}
		else if(tok==' ') continue;
		else{
			op2=LBSPop(&stack);
			op1=LBSPop(&stack);


			switch(tok){
				case '+':
					LBSPush(&stack,op1+op2);
					break;
				case '-':
					LBSPush(&stack,op1-op2);
					break;
				case '*':
					LBSPush(&stack,op1*op2);
					break;
				case '/':
					LBSPush(&stack,op1/op2);
					break;
			}
		}
	}
	return LBSPop(&stack);
}