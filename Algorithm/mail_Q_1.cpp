/*
모든 원소가 정확히 두번 나타나는 정수 배열이 있습니다.
이 배열에서 무작위로 두개의 다른 원소를 제거합니다.
이 배열에서 제거된 두 원소 값을 구하시오.
제한 : 시간복잡도 O(n), 공간복잡도 O(1)

input : [2,1,5,6,6,1]
output : 2,5

input : [9,9,4,3]
output : 4,3

풀이 : A xor A 는 0 이기에 모든 값을 xor 하면 A xor B 가 남게된다.
그리고 A 와 B 는 다른 값일 것이기 때문에 서로 다른 값을 가지는 비트가 존재한다.
그 비트의 값이 0인 부분과 1인 부분을 나눠서 xor 연산을 다 하면
한 쪽에는 A가 남고 한 쪽에는 B가 남게된다.
*/

#include<iostream>

int main(){
	int arr[10]={5,2,3,5,2,3,8,9,1,8};
	int size=10;
	int value1=0;
	int value2=0;
	int x=0;
	
	for(int i=0;i<size;++i) x^=arr[i];
	x=x & -x;
	for(int i=0;i<size;++i){
		if(arr[i] & x) value1=value1^arr[i];
		else value2=value2^arr[i];
	}
	std::cout<<value1<<", "<<value2<<std::endl;
	return 0;
}
