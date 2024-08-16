/**
 * @file 정수삼각형_43105.cpp
 * @brief 프로그래머스 lv.3 정수삼각형
 * @version 0.1
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    vector<vector<int>> dp = triangle;
    dp[0][0] = triangle[0][0];
    for(int i=1; i<triangle.size(); i++) {
        for(int j=0; j<triangle[i].size(); j++) {
            int left = j-1;
            if (left >= 0 && left < triangle[i-1].size()) { // 범위 안에 들어오면
                dp[i][j] = max(dp[i][j], dp[i-1][left] + triangle[i][j]);
            }
            int right = j;
            if (right >= 0 && right < triangle[i-1].size()) { // 범위 안에 들어오면
                dp[i][j] = max(dp[i][j], dp[i-1][right] + triangle[i][j]);
            }
            
        }
    }
    return *max_element(dp[dp.size()-1].begin(), dp[dp.size()-1].end());
}