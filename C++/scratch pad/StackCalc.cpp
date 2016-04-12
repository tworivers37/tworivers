#include"StackCalc.h"

using namespace lStack;
using namespace StackCalc;
using namespace std;


namespace StackCalc{
	int Calc::priority(string op){
		if(op=="(" || op==")") return 0;
		if(op=="*" || op=="/") return 1;
		if(op=="+" || op=="-") return 2;
		return -1;
	}

	string Calc::realCalc(const char* op1,const char* op2,const string& op){
		switch(op.c_str()[0]){
			case '+':
				return to_string(atof(op2)+atof(op1));
			case '-':
				return to_string(atof(op2)-atof(op1));
			case '*':
				return to_string(atof(op2)*atof(op1));
			case '/':
				return to_string(atof(op2)/atof(op1));
		}
		return "";
	}

	string Calc::postStr(){
		ListStack<string> *stack=new ListStack<string>;
		string postfix="";

		for(string::size_type i=0;i<str.size();i++){
			string charToStr(1,str[i]);
			
			if(charToStr=="+" || charToStr=="-" || charToStr=="*" || charToStr=="/"){
				while(!stack->isEmpty() && (priority(charToStr)<=priority(stack->peek())))
					postfix+=stack->pop()+" ";
				stack->push(charToStr);
			}
			else if(charToStr=="(") stack->push(charToStr);
			else if(charToStr==")"){
				string tmp=stack->pop();
				while(tmp!="("){
					postfix+=tmp+" ";
					tmp=stack->pop();
				}
			}
			else postfix+=charToStr+" ";
		}
		while(!stack->isEmpty()) postfix+=stack->pop()+" ";
		return postfix;
	}

	double Calc::stackCalc(){
		ListStack<string> *stack=new ListStack<string>;
		string postfix=postStr();
		if(bResultCheck) return result;

		for(string::size_type i=0;i<postfix.size();i+=2){
			string charToStr(1,postfix[i]);
			if(charToStr=="+" || charToStr=="-" || charToStr=="*" || charToStr=="/"){
				string o1=stack->pop();
				string o2=stack->pop();

				stack->push(realCalc(o1.c_str(),o2.c_str(),charToStr));
			}
			else stack->push(charToStr);
		}
		result=atof(stack->pop().c_str());		
		bResultCheck=true;
		return result;
	}
}
