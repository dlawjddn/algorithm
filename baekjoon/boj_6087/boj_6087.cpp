/**
 * @file boj_6087.cpp
 * @brief 백준 gold3 레이저 통신
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
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
    int y, x, dir, door;

    bool operator<(Info other) const {
        return door > other.door;
    }
};
int sizeX, sizeY, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<pair<int, int> > points;
vector<vector<vector<int> > > visited;

void print_visited(){
    for(int d=0; d<4; d++) {
        cout<<"d: "<<d<<"\n";
        for(int y=0; y<sizeY; y++) {
            for(int x=0; x<sizeX; x++) {
                cout<<visited[y][x][d]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
}

Info make_info(int y, int x, int dir, int door) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    info.door = door;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int dijkstra() {
    priority_queue<Info> pq;
    auto[sy, sx] = points[0];
    for(int d=0; d<4; d++) {
        pq.push(make_info(sy, sx, d, 0));
        visited[sy][sx][d] = 0;
    }
    while(!pq.empty()) {
        auto[y, x, dir, door] = pq.top(); pq.pop();
        if (visited[y][x][dir] != door) continue;
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        if (check_outside(ny, nx) || maps[ny][nx] == '*') continue;
        
        // 거울을 설치하지 않는 경우
        if (visited[ny][nx][dir] > door) {
            pq.push(make_info(ny, nx, dir, door));
            visited[ny][nx][dir] = door;
        }

        // 거울을 설치하는 경우
        int ld = (dir+3) % 4; // 진행 방향 기준 왼쪽
        if (visited[ny][nx][ld] > door + 1) {
            pq.push(make_info(ny, nx, ld, door + 1));
            visited[ny][nx][ld] = door + 1;
        }
        int rd = (dir+5) % 4; // 진행 방향 기준 오른쪽
        if (visited[ny][nx][rd] > door + 1) {
            pq.push(make_info(ny, nx, rd, door + 1));
            visited[ny][nx][rd] = door + 1;
        }
    }
    auto[dy, dx] = points[1];
    return *min_element(visited[dy][dx].begin(), visited[dy][dx].end());
}

int main(){
    cin>>sizeX>>sizeY;
    maps.resize(sizeY);
    visited.resize(sizeY, vector<vector<int> >(sizeX, vector<int>(4, INF)));
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 'C') points.push_back(make_pair(y, x));
        }
    }
    cout<<dijkstra();
    //print_visited();
}