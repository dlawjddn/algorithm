/**
 * @file boj_5558.cpp
 * @brief 백준 gold5 チーズ (Cheese)
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, cheese_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<vector<vector<int> > > visited;

pair<pair<int, int>, int> make_double_pair(int y, int x, int cheese) {
    return make_pair(make_pair(y, x), cheese);
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
} 

int bfs(int sy, int sx) {
    queue<pair<pair<int, int>, int > > q;
    q.push(make_double_pair(sy, sx, 0));
    visited[sy][sx][0] = 1;
    while(!q.empty()) {
        auto[pos, cheese] = q.front(); q.pop();
        if (cheese == cheese_cnt) return visited[pos.first][pos.second][cheese] - 1;
        for(int d=0; d<4; d++) {
            int ny = pos.first + moveY[d];
            int nx = pos.second + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx][cheese] != 0 || maps[ny][nx] == 'X') continue;
            if (maps[ny][nx] == cheese + 1 + '0') {
                q.push(make_double_pair(ny, nx, cheese + 1));
                visited[ny][nx][cheese + 1] = visited[pos.first][pos.second][cheese] + 1;
            } else {
                q.push(make_double_pair(ny, nx, cheese));
                visited[ny][nx][cheese] = visited[pos.first][pos.second][cheese] + 1;
            }
        }
    }
    return -1;
} 

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX>>cheese_cnt;
    maps.resize(sizeY);
    visited.resize(sizeY, vector<vector<int> >(sizeX, vector<int>(cheese_cnt + 1, 0)));
    int startY, startX;
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 'S') startY = y, startX = x;
        }
    }
    cout<<bfs(startY, startX);
}