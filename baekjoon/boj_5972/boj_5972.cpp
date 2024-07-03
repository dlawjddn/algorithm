/**
 * @file boj_5972.cpp
 * @brief 백준 gold5 택배 배송
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그신이잖아~
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int pos, cost;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt = 0, line_cnt = 0;
vector<int> visited;
vector<vector<pair<int, int> > > maps(50001);

Info make_info(int pos, int cost) {
    Info info;
    info.pos = pos;
    info.cost = cost;
    return info;
}

int dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(1, 0));
    visited[1] = 0;
    while(!pq.empty()) {
        auto[pos, cost] = pq.top(); pq.pop();
        //cout<<pos<<"\n";
        if (visited[pos] != cost) continue;
        for(int d=0; d<maps[pos].size(); d++) {
            int npos = maps[pos][d].first;
            int ncost = cost + maps[pos][d].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_info(npos, ncost));
            visited[npos] = ncost;
        }
    }
    return visited[node_cnt];
}

int main(){
    cin>>node_cnt>>line_cnt;
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<line_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(dest, cost));
        maps[dest].push_back(make_pair(src, cost));
    }
    cout<<dijkstra();
}