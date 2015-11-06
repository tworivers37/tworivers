void InsertionSort(int arr[],int len){
	int i,j;
	int tmp;

	for(i=1;i<len;i++){
		tmp=arr[i];
		for(j=i-1;j>=0;j--){
			if(arr[j]>tmp) arr[j+1]=arr[j];
			else break;
		}
		arr[j+1]=tmp;
	}
}