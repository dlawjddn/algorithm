// #include <iostream>
// #include <vector>
// #include <algorithm>

// #define INF 987654321

// using namespace std;

// int kindof, target;
// vector<int> money;
// vector<vector<int> > dp;

// void print_dp() {
//     for(int y=0; y<dp.size(); y++) {
//         for(int x=0; x<dp[y].size(); x++) {
//             cout<<((dp[y][x] == INF) ? 0 : dp[y][x])<<' ';
//         }
//         cout<<"\n";
//     }
// }

// int main() {
//     cin >> kindof >> target;
//     money.resize(kindof);
//     dp.resize(kindof, vector<int>(target + 1, INF));
//     for (int i = 0; i < kindof; i++) cin >> money[i];

//     for (int k = 0; k < kindof; k++) dp[k][0] = 0;

//     for (int k = 0; k < kindof; k++) {
//         for (int m = 0; m <= target; m++) {
//             if (k == 0) {
//                 if (m % money[k] == 0) dp[k][m] = m / money[k];
//             } else {
//                 if (m - money[k] >= 0) {
//                     dp[k][m] = min(dp[k-1][m], dp[k][m-money[k]] + 1);
//                 } else {
//                     dp[k][m] = dp[k-1][m];
//                 }
//             }
//         }
//     }

//     print_dp();
//     return 0;
// }


#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

void print_dp(vector<int>& dp) {
    for(int i=0; i<dp.size(); i++) cout<<dp[i]<<" ";
    cout<<"\n";
}

int main() {
    int n, m; cin>>n>>m;
    vector<int> kindof(n);
    vector<int> dp(m+1, INF);
    for(int i=0; i<n; i++) cin>>kindof[i];
    dp[0] = 0;

    for(int k=0; k<n; k++) {
        for(int money=kindof[k]; money<=m; money++) {
            dp[money] = min(dp[money - kindof[k]] + 1, dp[money]);
        }
    }
    cout<<((dp.back() == INF) ? -1 : dp.back());
}