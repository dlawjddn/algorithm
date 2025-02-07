#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, dist = 0, password = 0;
vector<vector<int> > maps;
vector<pair<int, int> > pos;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void bfs(int sy, int sx) {
    queue<pair<int, int> > q;
    vector<vector<int> > visited(sizeY, vector<int>(sizeX, 0));
    q.push({sy, sx});
    visited[sy][sx] = 1;
    if (dist <= visited[sy][sx]) {
        if (dist == visited[sy][sx] && password < maps[sy][sx] * 2) password = maps[sy][sx] * 2;
        else if (dist < visited[sy][sx]) password = visited[sy][sx] * 2;
    }
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        if (dist <= visited[y][x]) {
            if (dist == visited[y][x] && password < maps[sy][sx] + maps[y][x]) password = maps[sy][sx] + maps[y][x];
            else if (dist < visited[y][x]) {
                dist = visited[y][x];
                password = maps[sy][sx] + maps[y][x];
            }
        }
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == 0 || visited[ny][nx] != 0) continue;
            q.push({ny, nx});
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 0) continue;
            pos.push_back({y, x});
        }
    }

    for(pair<int, int> start : pos) {
        bfs(start.first, start.second);
    }
    cout<<password;
}