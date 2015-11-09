#include "common.h"
#include "MergeSort.h"

void MergeSort(int arr[],int left,int right){
	int mid;
	if(left<right){
		mid=(left+right)/2;

		MergeSort(arr,left,mid);
		MergeSort(arr,mid+1,right);

		MergeTwoArea(arr,left,mid,right);
	}
}
void MergeTwoArea(int arr[],int left,int mid,int right){
	int fIdx=left;
	int rIdx=mid+1;
	int i;

	int *sortArray=(int*)malloc(sizeof(int)*(right+1));
	int sIdx=left;

	while(fIdx<=mid && rIdx<=right){
		if(arr[fIdx]<arr[rIdx]) sortArray[sIdx]=arr[fIdx++];
		else sortArray[sIdx]=arr[rIdx++];
		sIdx++;
	}

	if(fIdx>mid) for(i=rIdx;i<right;i++,sIdx++) sortArray[sIdx]=arr[i];
	else for(i=fIdx;i<mid;i++,sIdx++) sortArray[sIdx]=arr[i];

	for(i=left;i<=right;i++) arr[i]=sortArray[i];

	free(sortArray);
}