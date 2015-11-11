int BinarySearch(int arr[],int first,int last,int target){
	int mid;
	if(first>last) return -1;
	mid=(first+last)/2;

	if(arr[mid]==target) return mid;
	else if(arr[mid]>target) return BinarySearch(arr,first,mid-1,target);
	else return BinarySearch(arr,mid+1,last,target);
}