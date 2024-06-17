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