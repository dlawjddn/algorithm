/**
 * @file 땅따먹기_12913.cpp
 * @brief 프로그래머스 lv.2 땅따먹기
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > dp;

void print_dp() {
    for(int i=0; i<dp.size(); i++) {
        for(int j=0; j<dp[i].size(); j++) {
            cout<<dp[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int solution(vector<vector<int> > land){
    int answer = 0;
    dp.resize(land.size(), vector<int>(4, 0));
    dp[0] = land[0];
    for(int i=1; i<dp.size(); i++) {
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                if (j == k) continue;
                dp[i][j] = max(dp[i][j], land[i][j] + dp[i-1][k]);
            }
        }
    }
    return *max_element(dp[dp.size()-1].begin(), dp[dp.size()-1].end());
}