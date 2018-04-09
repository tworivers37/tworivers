/*
정수로된 배열이 주어지면, 각 원소가 자신을 뺀 나머지 원소들의 곱셈이 되게하라.

단, 나누기 사용 금지, O(n) 시간복잡도

예제)
input: [1, 2, 3, 4, 5]
output: [120, 60, 40, 30, 24]
*/

#include<iostream>

int main(){
        const int size=5;
        const int arr[size]={1,2,3,4,5};
        int arr_1[size];
        int arr_2[size];
        int result[size];
        int tmp=1;
        for(int i=0;i<size;++i){
                arr_1[i]=tmp;
                tmp*=arr[i];
        }
        tmp=1;
        for(int i=size-1;i>=0;--i){
                arr_2[i]=tmp;
                tmp*=arr[i];
        }
        for(int i=0;i<size;++i) result[i]=arr_1[i]*arr_2[i];

        for(auto p : result) std::cout<<p<<" ";
        std::cout<<std::endl;

        return 0;
}
