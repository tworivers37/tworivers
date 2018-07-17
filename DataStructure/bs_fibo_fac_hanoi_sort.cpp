int bs1(int *arr,int len,int target){
	int first=0;
	int last=len-1;
	while(first<last){
		int mid=(first+last)/2;
		if(arr[mid]==target) return mid;
		else if(arr[mid]>target) last=mid-1;
		else first=mid+1;
	}
	return -1;
}

int bs2(int *arr,int first,int last,int target){
	if(first>last) return -1;
	int mid=(first+last)/2;
	if(arr[mid]==target) return mid;
	else if(arr[mid]>target) return bs2(arr,first,mid-1,target);
	else return bs2(arr,mid+1,last,target);
}


int fac1(int n){
	if(n==2) return 2;
	return n*fac1(n-1);
}

int fac2(int n){
	int s=1;
	for(int i=2;i<=n;++i) s*=i;
	return s;
}

int fac3(int n,int m){
	if(n==m) return n;
	int mid=(n+m)/2;
	return fac3(n,mid)*fac3(mid+1,m);
}

int fac4(int n,int m){
	if(n==m) return n;
	else{
		int mid=(m-n)/2;
		int x=fac4(n,mid+n);
		int y=fac4(mid+n+1,m);
		return x*y;
	}
}

int fibo1(int n){
	//if(n==1) return 0;
	//if(n==2) return 1;
	if(n<1) return -1;
	if(n<3) return n-1;
	return fibo1(n-2)+fibo1(n-1);
}

int fibo2(int n){
	int first=0,second=1;
	//if(n==1) return 0;
	//if(n==2) return 1;
	if(n<1) return -1;
	if(n<3) return n-1;
	for(int i=3;i<=n;++i){
		second=first+second;
		first=second-first;
	}
	return second;
}

int _fibo3(int n,int first,int second){
	if(n==1) return first;
	return _fibo3(n-1,second,first+second);
}
int fibo3(int n){
	return _fibo3(n,0,1);
}

int fibo4(int n){
	//if(n==1) return 0;
	//if(n==2) return 1;
	if(n<1) return -1;
	if(n<3) return n-1;

	int *cache=new int[n+1];
	for(int i=0;i<n+1;++i)cache[i]=-1;
	cache[1]=0;cache[2]=1;

	for(int i=3;i<=n;++i) cache[i]=cache[i-2]+cache[i-1];
	
	return cache[n];
}
int *cache=new int[100]; //-1 로 초기화
int fibo5(int n){
	//if(n==1) return 0;
	//if(n==2) return 1;
	if(n<1) return -1;
	if(n<3) return n-1;
	if(cache[n]!=-1) return cache[n];
	return cache[n]=fibo5(n-1)+fibo5(n-2);
}

void hanoi(int n,int a,int b,int c){
	if(n==1) cout<<n<<" : "<<a<<" -> "<<c<<endl;
	else{
		hanoi(n-1,a,c,b);
		cout<<n<<" : "<<a<<" -> "<<c<<endl;
		hanoi(n-1,b,a,c);
	}
}

void swap(int *arr,int i,int j){
	int tmp=arr[i];
	arr[i]=arr[j];
	arr[j]=tmp;
}
void bubble(int *arr,int len){
	for(int i=0;i<len;++i)
		for(int j=0;j<len-i-1;++j)
			if(arr[j]>arr[j+1]) swap(arr,j,j+1);
}
void select(int *arr,int len){
	int idx;
	for(int i=0;i<len;++i){
		idx=i;
		for(int j=i+1;j<len;++j) if(arr[j]<arr[idx]) idx=j;
		swap(arr,i,idx);
	}
}
void insertion(int *arr,int len){
	int tmp,j;
	for(int i=1;i<len;++i){
		tmp=arr[i];
		for(j=i-1;j>=0;--j){
			if(arr[j]>tmp)arr[j+1]=arr[j];
			else break;
		}
		arr[j+1]=tmp;
	}
}

void mergeSort(int *arr,int left,int mid,int right){
	int leftStart=left;
	int rightStart=mid+1;
	int *tmp=new int[right+1];
	int idx=left;

	while(leftStart<=mid && rightStart<=right){
		if(arr[leftStart]<arr[rightStart]) tmp[idx++]=arr[leftStart++];
		else tmp[idx++]=arr[rightStart++];
	}

	if(leftStart>mid) while(rightStart<=right) tmp[idx++]=arr[rightStart++];
	else while(leftStart<=mid) tmp[idx++]=arr[leftStart++];
	
	for(int i=left;i<=right;++i) arr[i]=tmp[i];
}
void merge(int *arr,int left,int right){
	if(left<right){
		int mid=(left+right)/2;
		merge(arr,left,mid);
		merge(arr,mid+1,right);
		mergeSort(arr,left,mid,right);
	}
}

int partition(int *arr,int left,int right){
	int pivot=left;
	int start=left+1;
	int end=right;

	while(start<=end){
		while(start<=right && arr[start]<=arr[pivot]) ++start;

		while(end>=left+1 && arr[end]>=arr[pivot] && start<=end) --end;
		//위 while문 끝 start<=end 특정 조건에서 (ex. {1,1,1,1,1,2,1} ) 반복을 줄여 줄 수 있음.

		if(start<=end) swap(arr,start,end);
	}
	swap(arr,pivot,end);
	return end;
}
void quick(int *arr,int left,int right){
	if(left<right){
		int pivot=partition(arr,left,right);
		quick(arr,left,pivot-1);
		quick(arr,pivot+1,right);
	}
}
