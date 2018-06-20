/*
숫자만큼 배열의 앞 쪽 부분을 배열의 뒷 부분으로 이동.
ex) num=2 , arr ={1,2,3,4,5} ---> arr = {3,4,5,1,2}
*/

#include<iostream>
#include<vector>
void swap(int& v1,int& v2){
        int tmp(std::move(v1));
        v1=std::move(v2);
        v2=std::move(tmp);
}
void reverse(int first,int last,std::vector<int>& arr){
        while(first<last){
                swap(arr[first],arr[last]);
                ++first;
                --last;
        }
}
void solv(int& num,std::vector<int>& arr){
        int length=arr.size();
        if(length<num||num<0) return;
        reverse(0,num-1,arr);
        reverse(num,length-1,arr);
        reverse(0,length-1,arr);
}
int main(){
        std::vector<int> arr={1,2,3,4,5};
        int num=2;
        solv(num,arr);

        for(auto a : arr) std::cout<<a<<" ";
        std::cout<<"\n";

        return 0;
}




