/*
  bubble sort 개선
*/
#include<iostream>

void bubble(int* arr, const int n){
	bool sorted=true;
	for(int i=n-1;i>1;--i){
		sorted=true;
		for(int j=0;j<i-1;++j){
			if(arr[j]>arr[j+1]){
				int tmp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=tmp;
				sorted=false;
			}
		}
		if(sorted) return;
	}
}

int main(){
	const int n=5;
	int arr[n]={7,4,5,1,8};
	bubble(arr,n);
	for(int i=0;i<n;++i) std::cout<<arr[i]<<std::endl;
	return 0;
}
