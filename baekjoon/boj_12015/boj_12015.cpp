#include <iostream>
#include <vector>
using namespace std;
int arr[1000000], len=0;
vector<int> ans;
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>len;
    for(int i=0; i<len; i++) cin>>arr[i];
    ans.push_back(arr[0]);
    for(int j=1; j<len; j++){
        if (ans.back()<arr[j]) ans.push_back(arr[j]);
        else ans[lower_bound(ans.begin(), ans.end(), arr[j])-ans.begin()] = arr[j];
    }
    cout<<ans.size()<<"\n";
}