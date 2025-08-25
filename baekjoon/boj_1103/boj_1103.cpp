#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cycle = false;
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, answer = -1;
vector<string> maps;
vector<vector<bool> > visited;
vector<vector<int> > dp;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void dfs(int y, int x, int cnt) {
    if (cycle) return ;
    answer = max(answer, cnt);
    if (check_outside(y, x) || maps[y][x] == 'H') return ;
    
    if (dp[y][x] >= cnt) return ;
    dp[y][x] = cnt;
    
    if (visited[y][x]) {
        cycle = true;
        return ;
    }
    visited[y][x] = true;
    

    int jump = maps[y][x] - '0';
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d] * jump;
        int nx = x + moveX[d] * jump;
        dfs(ny, nx, cnt + 1);
    }
    visited[y][x] = false;
}

int main() {
    cin>>sizeY>>sizeX;
    dp.resize(sizeY, vector<int>(sizeX, -1));
    visited.resize(sizeY, vector<bool>(sizeX, false));
    for(int y=0; y<sizeY; y++) {
        string row; cin>>row;
        maps.push_back(row);
    }
    dfs(0, 0, 0);
    cout<<(cycle ? -1 : answer);
}