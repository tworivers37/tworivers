#include "QuickSort.h"

void Swap(int arr[],int idx1,int idx2){
	int tmp=arr[idx1];
	arr[idx1]=arr[idx2];
	arr[idx2]=tmp;
}

int Partition(int arr[],int left,int right){
	//pivot을 가장 왼쪽으로 선택
	int pivot=arr[left];
	int low=left+1;
	int high=right;

	while(low<=high){
		while(pivot>=arr[low] && low<=right) low++;
		while(pivot<=arr[high] && high>=(left+1)) high--;
		if(low<=high) Swap(arr,low,high);
	}
	Swap(arr,left,high);
	return high; //정렬 기준에 알맞는 위치로 이동된 pivot의 index
}

void QuickSort(int arr[],int left,int right){
	int pivot;
	if(left<=right){
		pivot=Partition(arr,left,right);
		QuickSort(arr,left,pivot-1); //왼쪽
		QuickSort(arr,pivot+1,right); //오른쪽
	}
}
