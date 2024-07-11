/**
 * @file boj_2151.cpp
 * @brief 백준 gold3 거울 설치
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제 제발 똑바로 읽자 정우야.. 에휴.. 이걸 왜 헤매냐
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 987654321
using namespace std;

struct Info {
    int y, x, dir;
};
int sq_size, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<pair<int, int> > doors;
vector<vector<vector<int> > > visited;

Info make_info(int y, int x, int dir) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dijkstra() {
    queue<Info> q;
    auto[sy, sx] = doors[0];
    for(int d=0; d<4; d++) {
        q.push(make_info(sy, sx, d));
        visited[sy][sx][d] = 0;
    }
    while(!q.empty()) {
        auto[y, x, dir] = q.front(); q.pop();
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        if (check_outside(ny, nx) || maps[ny][nx] == '*') continue;
        
        if (maps[ny][nx] == '.' || maps[ny][nx] == '#') {
            if (visited[ny][nx][dir] <= visited[y][x][dir]) continue;
            q.push(make_info(ny, nx, dir));
            visited[ny][nx][dir] = visited[y][x][dir];
        }
        else {
            // 거울을 설치하지 않고 그냥 통과하는 경우
            if (visited[ny][nx][dir] <= visited[y][x][dir]) continue;
            q.push(make_info(ny, nx, dir));
            visited[ny][nx][dir] = visited[y][x][dir];

            // 거울을 설치하는 경우
            int ld = (dir+3)%4; // 진행방향 기준 왼쪽으로 회전
            int rd = (dir+5)%4; // 진행방향 기준 오른쪽으로 회전

            // 현재 진행방향 기준 왼쪽
            if (visited[ny][nx][ld] <= visited[y][x][dir] + 1) continue;
            q.push(make_info(ny, nx, ld));
            visited[ny][nx][ld] = visited[y][x][dir] + 1;

            // 현재 진행방향 기준 오른쪽
            if (visited[ny][nx][rd] <= visited[y][x][dir] + 1) continue;
            q.push(make_info(ny, nx, rd));
            visited[ny][nx][rd] = visited[y][x][dir] + 1;
        }
    }
    auto[dy, dx] = doors[1];
    return *min_element(visited[dy][dx].begin(), visited[dy][dx].end());
}

int main() {
    cin>>sq_size;
    maps.resize(sq_size);
    visited.resize(sq_size, vector<vector<int> >(sq_size, vector<int>(4, INF)));
    for(int y=0; y<sq_size; y++) {
        cin>>maps[y];
        for(int x=0; x<sq_size; x++) {
            if (maps[y][x] == '#') doors.push_back(make_pair(y, x));
        }
    }
    cout<<dijkstra();
}