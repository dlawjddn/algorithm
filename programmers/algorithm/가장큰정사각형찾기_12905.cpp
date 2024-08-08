/**
 * @file 가장큰정사각형찾기_12905.cpp
 * @brief 프로그래머스 lv.2 가장 큰 정사각형 찾기
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > dp;

void print_dp() {
    for(int y=0; y<dp.size(); y++) {
        for(int x=0; x<dp[0].size(); x++) {
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    if (board.size() == 1 && board[0].size() == 1) {
        return board[0][0];
    }
    dp.resize(board.size(), vector<int>(board[0].size(), 0));
    for(int y=0; y<dp.size(); y++) {
        if (board[y][0] == 0) dp[y][0] = 0;
        else dp[y][0] = 1;
    }
    for(int x=0; x<dp[0].size(); x++) {
        if (board[0][x] == 0) dp[0][x] = 0;
        else dp[0][x] = 1;
    }
    
    for(int y=1; y<board.size(); y++) {
        for(int x=1; x<board[y].size(); x++) {
            if (board[y][x] == 1) {
                dp[y][x] = min(dp[y-1][x], min(dp[y][x-1], dp[y-1][x-1])) + 1;
                answer = max(answer, dp[y][x]);
            } else dp[y][x] = 0;
        }
    }
    return answer * answer;
}
