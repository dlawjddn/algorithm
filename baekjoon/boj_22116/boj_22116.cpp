/**
 * @file boj_22116.cpp
 * @brief 백준 gold4 창영이와 퇴근
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;
struct Info {
    int y, x, max_cost;
    bool operator<(Info other) const {
        return max_cost > other.max_cost;
    }
};
int sq_size, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;

Info make_info(int y, int x, int max_cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.max_cost = max_cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(0, 0, 0));
    visited[0][0] = 0;
    while(!pq.empty()) {
        auto[y, x, cost] = pq.top(); pq.pop();
        if (visited[y][x] != cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx)) continue;
            int ncost = max(cost, abs(maps[ny][nx] - maps[y][x]));
            if (visited[ny][nx] <= ncost) continue;
            pq.push(make_info(ny, nx, ncost));
            visited[ny][nx] = ncost;
        }
    }
    return visited[sq_size - 1][sq_size - 1];
}

int main(){
    cin>>sq_size;
    maps.resize(sq_size, vector<int>(sq_size));
    visited.resize(sq_size, vector<int>(sq_size, INF));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    cout<<dijkstra();
}