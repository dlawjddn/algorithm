#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    int cnt, k; cin>>cnt>>k;
    vector<int> a(cnt, 0);
    vector<int> b(cnt, 0);
    for(int i=0; i<cnt; i++) cin>>a[i];
    for(int i=0; i<cnt; i++) cin>>b[i];
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    int check_point = 0;
    for(int i=0; i<k; i++) {
        if (a[i] >= b[i]) break;
        swap(a[i], b[i]);
    }
    cout<<accumulate(a.begin(), a.end(), 0);
}