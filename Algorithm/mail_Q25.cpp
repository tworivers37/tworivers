/*
정렬된 정수 배열이 있습니다. 이 배열의 모든 원소들을 오른쪽으로 랜덤하게 Z번 이동하였습니다.
예를 들면 [1, 2, 3, 4, 5] -> [3, 4, 5, 1, 2].
이런 배열과 정수 K 가 주어지면, 배열안에 K가 존재하는지 찾으시오.
존재한다면 배열의 인덱스, 존재하지 않다면 -1 을 리턴하시오.
시간복잡도 제한 O(log N).

input: [3, 4, 5, 1, 2], 4
output: 1

input: [2, 4, 5, 1], 3
output: -1

input: [4, 6, 7, 8, 1, 2, 3], 5
output: -1

풀이:binary search 로 z를 구하고 다시 binary search 를 통해 값의 유무를 확인한다.
오름차순으로 정렬된 배열의 앞 부분이 뒤쪽으로 넘어간거기 때문에 arr[first]<arr[mid] 가 아닌 곳을 찾아서
범위를 좁혀나가면 z 를 구할 수 있음. 그리고 유무를 확인하기 위한 binary search를 해야하는데,
비교하는 값은 mid의 값과 target의 값이기 때문에 일반적인(0~n) binary search에서 구해지는 mid 값만
상대적인 위치를 구해서 target 값과 비교하면 됨.

*/

#include<iostream>
int main(){
        const int n=14;
        int arr[n]={5,6,7,10,12,15,19,22,23,25,28,1,2,3};
        int target=28;

        int first=0,last=n-1;
        int result=-1;
        while(first<last){
                int mid=(first+last)/2;
                if(arr[mid]>arr[first]) first=mid;
                else last=mid;
        }
        int diff=n-1-last;
        first=0;
        last=n-1;
        while(first<=last){
                int mid=(first+last)/2;
                int tmp=mid;
                if(mid>=diff) tmp-=diff;
                else tmp=n-(diff-mid);
                if(arr[tmp]>target) last=mid-1;
                else if(arr[tmp]<target) first=mid+1;
                else{
                        result=tmp;
                        break;
                }
        }
        std::cout<<result<<std::endl;
        return 0;
}
