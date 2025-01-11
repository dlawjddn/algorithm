#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int days, answer = 0;
vector<pair<int, int> > info;
vector<int> dp;

void print_dp() {
    for(int i=0; i<dp.size(); i++) {
        cout<<dp[i]<<" ";
    }
    cout<<"\n";
}

int main() {
    cin>>days;
    info.resize(days);
    dp.resize(days, 0);
    for(int i=0; i<days; i++) {
        int cost_day, cost_money; cin>>cost_day>>cost_money;
        info[i] = {cost_day, cost_money};
    }
    
    int after_meeting = info[0].first - 1;
    int earn_money = info[0].second;
    if (after_meeting <= days) dp[after_meeting] = earn_money;

    for(int i=1; i<days; i++) {
        dp[i] = max(dp[i-1], dp[i]);
        int after_meeting = i + info[i].first - 1;
        int earn_money = info[i].second;

        if (after_meeting >= days) continue;
        dp[after_meeting] = max(dp[after_meeting], dp[i - 1] + earn_money);
    }
    cout<<dp.back();

}