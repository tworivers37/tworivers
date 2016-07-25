/*
0���� �����
�ð� ����: 1 Sec  �޸� ����: 128 MB
[����]
���� ����
1���� N������ ���� ���������� ������ ���� 1 2 3 ... N�� ��������.

�׸��� '+'�� '-', �Ǵ� ' '(����)�� ������ ���� ���̿� ��������('+'�� ���ϱ�, '-'�� ����, 
' '(����)�� ���ڸ� �̾� ���̴� ���� ���Ѵ�). �̷��� ���� ������ ���� 0�� �Ǵ� ��� ��츦 ã�ƺ���

�Է�
ù��° �ٿ� �׽�Ʈ ���̽��� ������ �־�����(<10).

�� �׽�Ʈ ���̽��� �ڿ��� N�� �־�����(3 <= N <= 9).

���
�� �׽�Ʈ ���̽��� ����  ����� 0�� �Ǵ� ��� ������  ���������� ����Ѵ�. �� �׽�Ʈ ���̽��� ����� �� ���� ��� �����Ѵ�.

(����, ' '�� ASCII ���� 32 �̰� '+'�� 43, '-'  45�̴�.)

(����2, "1 2" �� "1+2"���� ���������� �ռ� �����̴�.)

�Է� ����
2
3
7
��� ����
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

//exeFunc(arr,0,n,0)
//cIdx�� ���� ������ ��ȣ ��ġ
void exeFunc(int *arr,int cIdx,int nIdx,int ch){
	int i;
	int sum=1;

	//0,1,2 -> +,-,' '

	if(cIdx>=nIdx-2){
		for(i=2;i<nIdx;i+=2){
			if(arr[i]==0) //+
				sum+=arr[i+1];
			else if(arr[i]==1) //-
				sum-=arr[i+1];
			else{//' '
				if(arr[i-2]==1) sum+=(arr[i-1]*-10-arr[i+1])+arr[i-1];
				else sum+=(arr[i-1]*10+arr[i+1])-arr[i-1];
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
	}
	else{
		cIdx+=2;
		arr[cIdx]=ch;
		//���ȣ��
		for(i=0;i<3;i++){
			exeFunc(arr,cIdx,nIdx,ch);
			arr[cIdx]=i+1;
		}
	}
}

void zeroFunc(int *n,int size){
	int i=0,j=0,k=1;
	int *arr;
	int nIdx;

	//���ڴ� Ȧ�� �ε���
	//��ȣ�� ¦�� �ε��� 2����
	for(i=0;i<size;i++){
		nIdx=n[i]*2;
		arr=(int*)malloc(nIdx*sizeof(int));
		arr[0]=99999;
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

