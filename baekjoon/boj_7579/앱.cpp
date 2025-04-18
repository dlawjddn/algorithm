#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 987654321

int app_cnt, need_mem;
vector<int> mems;
vector<int> costs;
vector<vector<pair<long long, long long> > > dp;

int main() {
    cin>>app_cnt>>need_mem;
    for(int i=0; i<app_cnt; i++) {
        int mem; cin>>mem;
        mems.push_back(mem);
    }
    for(int i=0; i<app_cnt; i++) {
        int cost; cin>>cost;
        costs.push_back(cost);
    }
    int max_cost = 100 * app_cnt;
    vector<vector<int> > dp(app_cnt + 1, vector<int>(max_cost + 1, 0));
    for(int i=1; i<=app_cnt; i++) {
        for(int j=0; j<=max_cost; j++) {
            if (j < costs[i-1]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j - costs[i-1]] + mems[i-1]);
        }
    }
    for(int i=0; i<=max_cost; i++) {
        if (dp[app_cnt][i] >= need_mem) {
            cout<<i;
            break;
        }
    }
}