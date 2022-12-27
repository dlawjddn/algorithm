#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){
    string src;
    string bomb;
    string ans;
    cin>>src>>bomb;
    for(int i=0; i<src.length(); i++){
        ans+=src[i];
        if (ans[ans.length()-1]==bomb[bomb.length()-1] && ans.length()>=bomb.length()){
            int cnt=1;
            for(int j=bomb.length()-2; j>=0; j--){
                if (ans[ans.length()-1 -(bomb.length()-1-j)] ==bomb[j])
                cnt++;
            }
            if (cnt==bomb.length()){
                for(int a=0; a<bomb.length(); a++) ans.pop_back();
            }
        }
    }
    if (ans.length()) cout<<ans;
    else cout<<"FRULA";
}