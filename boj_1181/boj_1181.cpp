#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool compare (string a, string b){
    if (a.size()==b.size()) return a < b;
    else return a.size() < b.size();
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int len=0;
    vector<string> v;
    cin>>len;
    v.push_back("A");
    for(int i=0; i<len; i++){
        string temp;
        cin>>temp;
        v.push_back(temp);
    }
    sort(v.begin(), v.end(), compare);
    for(int a=1; a<v.size(); a++) {
        if (v[a]==v[a-1]) continue;
        cout<<v[a]<<"\n";
    }
}