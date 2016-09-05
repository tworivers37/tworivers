#include<iostream>
using namespace std;
void fib(int input){
    int *d=new int[input+1];
    int **cnt=new int*[2];
    for(int i=0;i<2;i++){
        cnt[i]=new int[input+1];
       for(int j=0;j<=input;j++)cnt[i][j]=0;
    }
    cnt[0][0]=1;cnt[0][1]=0;
    cnt[1][0]=0;cnt[1][1]=1;
   
    d[0]=0;d[1]=1;
    for(int i=2;i<=input;i++){
        d[i]=d[i-1]+d[i-2];
        cnt[0][i]=cnt[0][i-1]+cnt[0][i-2];
        cnt[1][i]=cnt[1][i-1]+cnt[1][i-2];
    }
   cout<<cnt[0][input]<<" "<<cnt[1][input]<<endl;
}
int main(){
    int cnt,input;
    cin>>cnt;
    while(cnt--){
        cin>>input;
        fib(input);
    }
    return 0;
}
