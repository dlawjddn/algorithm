#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > dp;

void print_dp() {
    for(int y=0; y<dp.size(); y++) {
        for(int x=0; x<dp[y].size(); x++) {
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int main() {
    string str1, str2; cin>>str1>>str2;
    dp.resize(str1.size(), vector<int>(str2.size(), 0));

    bool flag = false;
    for(int y=0; y<str1.size(); y++) {
        if (flag) dp[y][0] = 1;
        if (str1[y] == str2[0]) {
            flag = true;
            dp[y][0] = 1;
        }
    }

    flag = false;
    for(int x=0; x<str2.size(); x++) {
        if (flag) dp[0][x] = 1;
        if (str2[x] == str1[0]) {
            flag = true;
            dp[0][x] = 1;
        }
    }
    //print_dp();
    for(int y=1; y<dp.size(); y++) {
        for(int x=1; x<dp[y].size(); x++) {
            if (str1[y] == str2[x]) {
                dp[y][x] = dp[y-1][x-1] + 1;
            } else dp[y][x] = max(dp[y-1][x], dp[y][x-1]);
        }
    }
    cout<<max(str1.size(), str2.size()) - dp[str1.size() - 1][str2.size() - 1];
}