#include<stdio.h>
#include<stdlib.h>

//cIdx는 이제 지정할 연산기호 위치
//ch는 연산기호
void exeFunc(int *arr,int cIdx,int nIdx,int ch){
	int i;
	int sum=0;
	int *tmp,tmpCnt=1;

	//0,1,2 -> +,-,' '
	if(cIdx>=nIdx-2){
		tmp=(int*)malloc(sizeof(int)*nIdx);
		tmp[0]=0;

		//' ' 때문에 tmp 배열에 맞춰서 배열.
		for(i=1;i<nIdx;i++){
			if(arr[i]==2 && i%2==0){
				tmp[tmpCnt-1]*=10;
				tmp[tmpCnt-1]+=arr[i+1];
				i++;
			}
			else tmp[tmpCnt++]=arr[i];
		}

		//계산
		for(i=0;i<tmpCnt;i++){
			if(i%2==0){
				if(tmp[i]==0) sum+=tmp[i+1];
				else sum-=tmp[i+1];
			}
		}
		if(sum==0){
			for(i=1;i<nIdx;i++){
				if(i%2==0){
					if(arr[i]==0) printf("+");
					else if(arr[i]==1) printf("-");
					else if(arr[i]==2) printf(" ");
				}
				else printf("%d",arr[i]);
			}
			printf("\n");
		}
		sum=0;
		free(tmp);
	}
	else{
		cIdx+=2;
		arr[cIdx]=ch;
		for(i=0;i<3;i++){
			exeFunc(arr,cIdx,nIdx,ch);
			arr[cIdx]=i+1;// 다음 기호(+ -> - -> ' ')
		}
	}
}

void zeroFunc(int *n,int size){
	int i=0,j=0,k=1;
	int *arr;
	int nIdx;

	//숫자는 홀수 인덱스
	//기호는 짝수 인덱스 2부터
	for(i=0;i<size;i++){
		nIdx=n[i]*2;
		arr=(int*)malloc(nIdx*sizeof(int));
		arr[0]=1;
		for(j=1;j<=nIdx;j+=2) arr[j]=k++;
		exeFunc(arr,0,nIdx,0);
		printf("\n");
		k=1;
		free(arr);
	}
}

int main(){
	int size;
	int *n;
	int i;
	scanf("%d",&size);
	n=(int*)malloc(size*sizeof(int));

	for(i=0;i<size;i++)scanf("%d",&n[i]);
	zeroFunc(n,size);

	return 0;
}
