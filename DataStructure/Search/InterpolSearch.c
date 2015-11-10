#include "InterpolSearch.h"

int ISearch(int arr[],int first,int last,int target){
	int s;
	//보간탐색
	//데이터 값과 데이터가 저장된 위치의 인덱스 값이 비례한다고 가정
	//정렬된 상태의 배열
	s=((double)(target-arr[first])/(arr[last]-arr[first]) * (last-first))+first;
	if(arr[first]>target || arr[last]<target) return -1;

	if(arr[s]==target) return s;
	else if(target<arr[s]) return ISearch(arr,first,s-1,target);
	else return ISearch(arr,s+1,last,target);
}