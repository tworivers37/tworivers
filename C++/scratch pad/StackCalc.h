#ifndef _STACK_CALC_H_
#define _STACK_CALC_H_

#include<iostream>
#include<string>
#include"Stack.h"
#include<cmath>

using namespace std;

namespace StackCalc{	
	class Calc{
		private:
			string str;
			bool bResultCheck;
			double result;

			int priority(string op);
			string realCalc(const char* op1,const char* op2,const string& op);
			string postStr();
		public:
			Calc(const string& _str):str(_str),bResultCheck(false){}
			~Calc(){}
			double stackCalc();
	};
}

#endif