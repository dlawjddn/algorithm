#include <iostream>
#include <stack>
using namespace std;
stack<char> s;
string closeEye(string str){
    string str2;
    for(int i=0; i<str.size(); i++){
        if (i%2==0) str2 += str[i];
        else s.push(str[i]);
    }
    while(!s.empty()){
        str2 += s.top();
        s.pop();
    }
    return str2;
}
int findCycle(string str){ // n번 해야 자기 자신으로 돌아옴
    string temp =str;
    int cycle=0;
    while(1){
        temp = closeEye(temp);
        cycle++;
        if (temp == str) break;
    }
    return cycle;
}
int main(){
    string str;
    int num =0, cycle=0;
    cin>>num>>str;
    cycle = findCycle(str);
    cycle = num % cycle;
    string ans = str;
    for(int i=0; i<cycle; i++){
        ans = closeEye(ans);
    }
    cout<<ans;
}