/**
 * @file 보행자천국_1832.cpp
 * @brief 
 * @version 0.1
 * @date 2024-06-21
 * 
 * @copyright Copyright (c) 2024
 * 
 * 처음으로 카카오 문제를 내 생각으로 해결한 문제.. 야호~ (문제가 쉽긴 했다..)
 * 
 */
#include <vector>
#include <iostream>

using namespace std;

int MOD = 20170805;

void print_dp(vector<vector<int> > dp){
    for(int y=0; y<dp.size(); y++){
        for(int x=0; x<dp[0].size(); x++){
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int solution(int m, int n, vector<vector<int>> map) {
    vector<vector<int> > dp(m, vector<int>(n, 0));
    vector<vector<int> > dp_left(m, vector<int>(n, 0));
    vector<vector<int> > dp_up(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for(int y=1; y<m; y++){
        if (map[y][0] == 1) break;
        dp_up[y][0] = 1;
        dp[y][0] += 1;
    }
    for(int x=1; x<n; x++){
        if (map[0][x] == 1) break;
        dp_left[0][x] = 1;
        dp[0][x] += 1;
    }
    for(int y=1; y<m; y++){
        for(int x=1; x<n; x++){
            if (map[y][x] == 1) continue;
            else {
                // 윗 방향에서 오는 경우의 수 확인 완료
                int uy = y - 1;
                int ux = x;
                if (map[uy][ux] == 2) { 
                    dp_up[y][x] = dp_up[uy][ux] % MOD;
                } else if (map[uy][ux] == 0) {
                    dp_up[y][x] = dp[uy][ux] % MOD;
                } else {
                    dp_up[y][x] = 0;
                }
                // 왼쪽 방향에서 오는 경우의 수 확인 완료
                int ly = y;
                int lx = x - 1;
                if (map[ly][lx] == 2) {
                    dp_left[y][x] = dp_left[ly][lx] % MOD;
                } else if (map[ly][lx] == 0) {
                    dp_left[y][x] = dp[ly][lx] % MOD;
                } else {
                    dp_left[y][x] = 0;
                }
                dp[y][x] = (dp_left[y][x] + dp_up[y][x]) % MOD;
            }
        }
    }
    
    return dp[m-1][n-1] % MOD;
}