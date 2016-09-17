int k;
int solve(int s, int e,int *A){
	int m;
	while(e-s>0){
		m=(s+e)/2;


		//n개로 이루어진 정수 집합에서 원하는 수 k 이상인 수가 처음으로 등장하는 위치
		//를 찾으시오
		//lower bound
		//if(A[m]<k) s=m+1;
		
		//n개로 이루어진 정수 집합에서 원하는 수 k보다 큰 수가 처음으로 등장하는 위치
		//를 찾으시오.
		//upper bound
		if(A[m]<=k)s=m+1;
		else e=m;
	}
	return e+1;
}
