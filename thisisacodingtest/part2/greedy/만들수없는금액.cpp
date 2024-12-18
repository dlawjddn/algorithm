#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int coin_cnt;
vector<int> coins;
vector<int> sum;
vector<bool> visited(1000001, false);

int main() {
    cin>>coin_cnt;
    sum.resize(coin_cnt, 0);
    for(int i=0; i<coin_cnt; i++) {
        int coin; cin>>coin;
        coins.push_back(coin);
        visited[coin] = true;
    }
    sort(coins.begin(), coins.end());
    sum[0] = coins[0];
    for(int i=1; i<coin_cnt; i++) {
        sum[i] = coins[i] + sum[i-1];
        visited[sum[i]] = true;
    }

    for(int i=0; i<coin_cnt; i++) {
        for(int j=i; j<coin_cnt; j++) {
            visited[sum[j] - sum[i]] = true;
        }
    }

    for(int i=1; i<visited.size(); i++) {
        if (!visited[i]) {
            cout<<i;
            break;
        }
    }
}