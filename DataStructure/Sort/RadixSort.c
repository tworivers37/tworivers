#include "RadixSort.h"

void RadixSort(int arr[],int num,int maxLen){//num:정렬대상 개수,maxLen:정렬대상 중 가장 긴 데이터 길이
	Queue bucket[BUCKET_NUM];
	int i,j,pos;
	int div=1;
	int radix;

	for(i=0;i<BUCKET_NUM;i++) LBQueueInit(&bucket[i]);

	for(pos=0;i<maxLen;pos++){
		for(i=0;i<num;i++){
			radix=(arr[i]/div)%10;
			LBEnqueue(&bucket[radix],arr[i]);
		}
		for(i=j=0;i<BUCKET_NUM;i++){
			while(!LBQueueIsEmpty(&bucket[i]))
				arr[j++]=LBDequeue(&bucket[i]);
		}
		div*=10;
	}
}