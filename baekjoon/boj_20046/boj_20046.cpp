/**
 * @file boj_20046.cpp
 * @brief 백준 gold4 Road Reconstruction
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int y, x, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;

Info make_info(int y, int x, int cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.cost = cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int dijkstra() {
    priority_queue<Info> pq;
    if (maps[0][0] == -1) return -1;
    pq.push(make_info(0, 0, maps[0][0]));
    visited[0][0] = maps[0][0];
    while(!pq.empty()) {
        auto[y, x, cost] = pq.top(); pq.pop();
        if (visited[y][x] != cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == -1) continue;
            int ncost = cost + maps[ny][nx];
            if (visited[ny][nx] <= ncost) continue;
            pq.push(make_info(ny, nx, ncost));
            visited[ny][nx] = ncost;
        }
    }
    return (visited[sizeY-1][sizeX-1] == INF ? -1 : visited[sizeY-1][sizeX-1]);
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX));
    visited.resize(sizeY, vector<int>(sizeX, INF));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    cout<<dijkstra();
}