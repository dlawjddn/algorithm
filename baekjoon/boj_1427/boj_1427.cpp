#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    string num;
    vector<int> ans;
    cin>>num;
    for(int i=0; i<num.size(); i++) ans.push_back(num[i]-'0');
    sort(ans.rbegin(), ans.rend());
    for(int j=0; j<ans.size(); j++) cout<<ans[j];
}