#include"StackCalc.h"
#include"Stack.h"
#include"Queue.h"

using namespace std;
using namespace StackCalc;

int main(){
	Calc c("4*(2+3)");
	cout<<c.stackCalc()<<endl;
	cout<<c.stackCalc()<<endl;
	
	return 0;
}