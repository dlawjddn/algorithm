/**
 * @file 거스름돈_12907.cpp
 * @brief 프로그래머스 lv.3 거스름돈
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

#define MOD 1000000007

using namespace std;

int solution(int n, vector<int> money) {
    int answer = 0;
    vector<int> dp(n+1, 0);
    dp[0] = 1;
    for(int coin : money) {
        for(int i=coin; i<=n; i++) {
            dp[i] = (dp[i] + dp[i-coin]) % MOD;
        }
    }
    return dp[n];
}