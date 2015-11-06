void SelectionSort(int arr[],int len){
	int i,j;
	int idx;
	int tmp;

	for(i=0;i<len-1;i++){
		idx=i;
		for(j=i+1;j<len;j++)
			 if(arr[j]<arr[idx]) idx=j;
		tmp=arr[idx];
		arr[idx]=arr[i];
		arr[i]=tmp;
	}
}