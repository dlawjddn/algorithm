#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> stores;
vector<int> dp;

int main() {
    int store_cnt; cin>>store_cnt;
    stores.resize(store_cnt);
    dp.resize(store_cnt, 0);
    for(int i=0; i<store_cnt; i++) cin>>stores[i];
    dp[0] = stores[0];
    dp[1] = stores[1];
    for(int i=2; i<store_cnt; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + stores[i]);
    }
    cout<<dp.back();
}