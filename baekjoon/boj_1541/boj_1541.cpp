#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
    int ans=0;
    bool isMinus=false;
    string str, num;
    cin>>str;
    for(int i=0; i<=str.size(); i++){
        if (str[i]=='-' || str[i]=='+' || i==str.size()){
            if (isMinus){
                ans-=stoi(num);
                num="";
            }
            else{
                ans+=stoi(num);
                num="";
                
            }
        }
        else num+=str[i];

        if (str[i]=='-') isMinus=true;
    }
    cout<<ans;
}