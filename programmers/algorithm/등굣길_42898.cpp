#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > dp(100, vector<int>(100, 0));

int solution(int m, int n, vector<vector<int>> puddles) {
    for(int i=0; i<puddles.size(); i++){
        dp[puddles[i][1]-1][puddles[i][0]-1] = -1;
    }
    bool yflag = false;
    for(int y=0; y<n; y++){
        if (dp[y][0] == -1){
            yflag = true;
        }
        if (!yflag)
            dp[y][0] = 1;
        else
            dp[y][0] = 0;
    }
    bool xflag = false;
    for(int x=0; x<m; x++){
        if (dp[0][x] == -1){
            xflag = true;
        }
        if (!xflag)
            dp[0][x] = 1;
        else
            dp[0][x] = 0;
    }
    
    for(int y=1; y<n; y++){
        for(int x=1; x<m; x++){
            if (dp[y][x] == -1) {
                continue;
            }
            int uy = y - 1;
            int ux = x;
            int ucnt = dp[uy][ux] % 1000000007;
            if (dp[uy][ux] == -1)
                ucnt = 0;

            int ly = y;
            int lx = x - 1;
            int lcnt = dp[ly][lx] % 1000000007;
            if (dp[ly][lx] == -1)
                lcnt = 0;
            
            dp[y][x] = (ucnt + lcnt) % 1000000007;
        }
    }
    return dp[n-1][m-1] % 1000000007;
}
/**
 * @file 등굣길_42898.cpp
 * @brief 프로그래머스 lv.3 등굣길
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 방법은 알고 있었는데 bfs 방법으로 하면 틀리는구나.. 주의하도록 해야겠다..
 * 방법의 수는 queue를 사용하지 말고 단순 dp를 활용해서 풀도록 하자..
 * 
 */
#include <string>
#include <vector>
#include <iostream>

#define MOD 1000000007

using namespace std;

vector<vector<int> > dp(100, vector<int>(100, 0));

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    dp.resize(n, vector<int>(m, 0));
    for(auto p : puddles) {
        int x = p[0] - 1;
        int y = p[1] - 1;
        dp[y][x] = -1;
    }
    // 세로 첫 줄
    for(int y=1; y<n; y++) {
        if (dp[y][0] == -1) break;
        dp[y][0] = 1;
    }
    // 가로 첫 줄
    for(int x=1; x<m; x++) {
        if (dp[0][x] == -1) break;
        dp[0][x] = 1;
    }
    for(int y=1; y<n; y++) {
        for(int x=1; x<m; x++) {
            if (dp[y][x] == -1) continue;
            int ucnt = (dp[y-1][x] == -1) ? 0 : dp[y-1][x];
            int lcnt = (dp[y][x-1] == -1) ? 0 : dp[y][x-1];
            dp[y][x] = (ucnt + lcnt) % MOD;
        }
    }
    return dp[n-1][m-1] % MOD;
}