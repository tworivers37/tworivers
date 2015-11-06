void BubbleSort(int arr[],int len){
	int i,j;
	int tmp;

	for(i=0;i<len-1;i++){
		for(j=0;j<len-i-1;j++){
			if(arr[i]>arr[i+1]){
				tmp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=tmp;
			}
		}

	}
}