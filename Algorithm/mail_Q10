/*
String이 주어지면, 중복된 char가 없는 가장 긴 서브스트링 (substring)의 길이를 찾으시오.  

예제)

Input: “aabcbcbc”

Output: 3 // “abc”



Input: “aaaaaaaa”

Output: 1 // “a”



Input: “abbbcedd”

Output: 4 // “bced”

*/

#include<iostream>

int main(){
        std::string input;
        std::cin>>input;

        int value=1;
        int arr[26]={0,};
        int max=-1;

        for(int i=0;i<input.size();++i){
                if(arr[input[i]-'a']!=0){
                        value=1;
                }
                arr[input[i]-'a']=value++;
                if(max<value-1) max=value-1;
        }
        std::cout<<"max length : "<<max<<std::endl;
        return 0;
}
