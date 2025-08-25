#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    for(int t=0; t<3; t++) {
        int kindof; cin>>kindof;
        int sum = 0;
        vector<pair<int, int> > coins;
        for(int i=0; i<kindof; i++) {
            int value, cnt; cin>>value>>cnt;
            coins.push_back({value, cnt});
            sum += (value * cnt);
        }
        if (sum % 2) {
            cout<<0<<'\n';
            continue;
        }
        
        vector<int> dp((sum / 2) + 1, -1);
        dp[0] = 0;
        for(int i=0; i<coins.size(); i++) {
            auto[value, cnt] = coins[i];
            for(int s=0; s<=(sum / 2); s++) {
                if (dp[s] >= 0) {
                    dp[s] = cnt;
                } else if (s >= value && dp[s - value] > 0) {
                    dp[s] = dp[s-value] - 1;
                } else dp[s] = -1;
            }
        }

        cout<<((dp.back() >= 0) ? 1 : 0)<<'\n';
    }
}