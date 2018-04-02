/*
길이가 같은 두 문자열(string) A 와 B가 주어지면, A 가 B 로 1:1 암호화 가능한지 찾으시오.

예제)
Input: “EGG”, “FOO”		
Output: True // E->F, G->O

Input: “ABBCD”, “APPLE”	
Output: True // A->A, B->P, C->L, D->E

Input: “AAB”, “FOO”		
Output: False
*/

#include<iostream>
int main(){       
  std::string str1,str2;
  bool s1=true,s2=true;
  std::cin>>str1;
  std::cin>>str2;
  if(str1.size()!=str2.size()) return 0;
  for(int i=1;i<str1.size();++i){
    if(str1[i-1]!=str1[i]) s1=!s1;
    if(str2[i-1]!=str2[i]) s2=!s2;
    if(s1!=s2){
      std::cout<<"false\n";
      return 0;
     }
  }
  std::cout<<"true\n";
  return 0;
}
