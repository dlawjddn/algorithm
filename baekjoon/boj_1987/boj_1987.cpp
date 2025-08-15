#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int answer = 0, sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<vector<bool> > visited;
vector<bool> alpha(26, false);

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void dfs(int y, int x, int cnt) {
    visited[y][x] = true;
    alpha[maps[y][x] - 'a'] = true;
    answer = max(answer, cnt);

    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || visited[ny][nx] || alpha[maps[ny][nx] - 'a']) continue;
        dfs(ny, nx, cnt + 1);
    }

    visited[y][x] = false;
    alpha[maps[y][x] - 'a'] = false;
}

int main() {
    cin>>sizeY>>sizeX;
    visited.resize(sizeY, vector<bool>(sizeX, false));
    for(int y=0; y<sizeY; y++) {
        string row; cin>>row;
        maps.push_back(row);
    }
    dfs(0, 0, 1);
    cout<<answer;
}