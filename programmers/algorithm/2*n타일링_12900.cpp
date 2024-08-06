/**
 * @file 2*n타일링_12900.cpp
 * @brief 프로그래머스 lv.2 2*n 타일링
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

#define MOD 1000000007

using namespace std;

vector<int> dp;

int solution(int n) {
    int answer = 0;
    dp.resize(n, 0);
    dp[0] = 1;
    dp[1] = 2;
    for(int i=2; i<n; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    }
    return dp[n-1];
}