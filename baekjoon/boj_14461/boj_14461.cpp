/**
 * @file boj_14461.cpp
 * @brief 백준 gold2 소가 길을 건너간 이유 7
 * @version 0.1
 * @date 2024-08-03
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
    int y, x, cost, cnt;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int sq_size, default_cost, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<vector<int> > > visited;

Info make_info(int y, int x, int cost, int cnt) {
    Info info;
    info.y = y;
    info.x = x;
    info.cost = cost;
    info.cnt = cnt;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(0, 0, 0, 0));
    visited[0][0][0] = 0;
    while(!pq.empty()) {
        auto[y, x, cost, cnt] = pq.top(); pq.pop();
        if (visited[y][x][cnt] != cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ncost = cost + default_cost;
            int ncnt = (cnt + 1) % 3;
            if (check_outside(ny, nx)) continue;
            if (ncnt == 0) ncost += maps[ny][nx];
            if (visited[ny][nx][ncnt] <= ncost) continue;
            pq.push(make_info(ny, nx, ncost, ncnt));
            visited[ny][nx][ncnt] = ncost;
        }
    }
    return *min_element(visited[sq_size-1][sq_size-1].begin(), visited[sq_size-1][sq_size-1].end());
}

int main(){
    cin>>sq_size>>default_cost;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    visited.resize(sq_size, vector<vector<int> >(sq_size, vector<int>(3, INF)));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    cout<<dijkstra();
}