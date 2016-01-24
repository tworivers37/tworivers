#include<iostream>
using namespace std;
enum class myEnum { //기본 int
	num1,num2,num3,num4=10,num5
};
enum class myEnum2: long { // 타입 변경
	num1,num2,num3,num4,num5
};

void main(){
	/*
	기존의 열거타입은 정수 타입으로 취급되어 서로 완전 별개인 열거 타입간에 비교 연산도 가능
	하지만 enum 클래스는 열거 값이 다른 정수 타입 변수로 자동 캐스팅 되지 않음.
	if(myEnum::num1 == 1){ // x

	}
	*/
	myEnum em;
	if(myEnum::num1 != myEnum::num2) cout<< "enum class" <<endl;
	if(myEnum::num1 == myEnum::num1) cout<< "enum class" <<endl;

	em=myEnum::num1;
	switch(em){
		//case 1 : 안됨
		case myEnum::num1:
			cout<<"switch num1"<<endl;
			break;
	}
}