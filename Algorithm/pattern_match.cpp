#include<iostream>
#include<string>
#include<cstring>

bool match(std::string str,std::string pattern){
        if(pattern.size()==0) return str.size()==0;

        bool bottom_up[str.size()+1][pattern.size()+1];

        memset(bottom_up,false,sizeof(bottom_up));

        bottom_up[0][0]=true;

        for(int i=1;i<=pattern.size();++i)
                if(pattern[i-1]=='*') bottom_up[0][i]=bottom_up[0][i-1];

        for(int i=1;i<=str.size();++i){
                for(int j=1;j<=pattern.size();++j){

                        if(pattern[j-1]=='*')
                                bottom_up[i][j]=bottom_up[i][j-1] || bottom_up[i-1][j];
                        else if(pattern[j-1]=='?' || str[i-1]==pattern[j-1])
                                bottom_up[i][j]=bottom_up[i-1][j-1];
                        else
                                bottom_up[i][j]=false;
                }
        }

        return bottom_up[str.size()][pattern.size()];
}


int main(){
        std::cout<<match("abc","a*c")<<std::endl;
        return 0;
}
