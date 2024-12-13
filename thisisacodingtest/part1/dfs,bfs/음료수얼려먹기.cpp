#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<bool> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void dfs(int y, int x) {
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || maps[ny][nx] == 1 || visited[ny][nx]) continue;
        visited[ny][nx] = true;
        dfs(ny, nx);
    }
}

void bfs(int sy, int sx) {
    queue<pair<int, int> > q;
    q.push({sy, sx});
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == 1 || visited[ny][nx]) continue;
            q.push({ny, nx});
            visited[ny][nx] = true;
        }
    }
}

int solve() {
    int result = 0;
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 0 && !visited[y][x]) {
                //dfs(y, x);
                bfs(y, x);
                result += 1;
            }
        }
    }
    return result;
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<bool>(sizeX, false));
    for(int y=0; y<sizeY; y++) {
        string row; cin>>row;
        for(int x=0; x<sizeX; x++) {
            maps[y][x] = row[x] - '0';
        }
    }
    cout<<solve();
}