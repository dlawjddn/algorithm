#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > dp;

int main() {
    int test_case; cin>>test_case;
    dp.resize(10001, vector<int>(4, 0));
    dp[0][1] = 1;
    dp[1][1] = 1;
    dp[2][1] = 1;
    dp[2][2] = 1;
    for(int i=3; i<=10000; i++) {
        dp[i][1] = dp[i-1][1];
        dp[i][2] = dp[i-2][1] + dp[i-2][2];
        dp[i][3] = dp[i-3][1] + dp[i-3][2] + dp[i-3][3];
    }
    for(int t=0; t<test_case; t++) {
        int problem; cin>>problem;
        cout<<(dp[problem][1] + dp[problem][2] + dp[problem][3])<< "\n";
    }
}