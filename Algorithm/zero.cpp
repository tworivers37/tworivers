/*
0으로 만들기
시간 제한: 1 Sec  메모리 제한: 128 MB
[제출]
문제 설명
1부터 N까지의 수를 순차적으로 나열한 수열 1 2 3 ... N을 생각하자.

그리고 '+'나 '-', 또는 ' '(공백)을 각각의 숫자 사이에 삽입하자('+'는 더하기, '-'는 빼기, 
' '(공백)은 숫자를 이어 붙이는 것을 뜻한다). 이렇게 만든 수식의 값이 0이 되는 모든 경우를 찾아보자

입력
첫번째 줄에 테스트 케이스의 개수가 주어진다(<10).

각 테스트 케이스엔 자연수 N이 주어진다(3 <= N <= 9).

출력
각 테스트 케이스에 대해  결과가 0이 되는 모든 수식을  사전순으로 출력한다. 각 테스트 케이스의 결과는 한 줄을 띄워 구분한다.

(참고, ' '는 ASCII 값이 32 이고 '+'는 43, '-'  45이다.)

(참고2, "1 2" 는 "1+2"보다 사전순으로 앞선 수식이다.)

입력 예시
2
3
7
출력 예시
1+2-3

1+2-3+4-5-6+7 
1+2-3-4+5+6-7 
1-2 3+4+5+6+7
1-2 3-4 5+6 7 
1-2+3+4-5+6-7 
1-2-3-4-5+6+7 
*/

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
		arr[0]=0;
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
