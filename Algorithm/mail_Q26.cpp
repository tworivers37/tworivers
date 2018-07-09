/*
정수 배열이 주어지면 , 배열 안의 모든 정수의 최대 공약수(GCD)를 구하시오.
시간 복잡도 제한 O(n)

input: [3, 2, 1]
output: 1

input: [2, 4, 6, 8]
output: 2
*/

#include<iostream>
int main(){
        const int n=6;
        int arr[n]={3,6,9,12,15,23};
        int min=-1;
        bool result=true;
        for(int i=0;i<n;++i)
                if(min==-1 || arr[min]>arr[i]) min=i;
        for(int i=0;i<n;++i)
                if(arr[i]%arr[min]!=0){
                        result=false;
                        break;
                }
        if(result) std::cout<<arr[min]<<std::endl;
        else std::cout<<1<<std::endl;
        return 0;
}