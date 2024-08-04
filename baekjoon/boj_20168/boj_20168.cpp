/**
 * @file boj_20168.cpp
 * @brief 백준 gold5 골목 대장 호석 - 기능성
 * @version 0.1
 * @date 2024-08-04
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
int node_cnt, edge_cnt, start, dest, budget;
vector<vector<pair<int, int> > > maps;
vector<int> visited;

int dijkstra() {
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push({0, {start, 0}});
    visited[start] = 0;
    while(!pq.empty()) {
        auto[max_cost, info] = pq.top(); pq.pop();
        auto[pos, total_cost] = info;
        if (visited[pos] != max_cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ntotal_cost = total_cost + maps[pos][x].second;
            int nmax_cost = max(max_cost, maps[pos][x].second);
            if (ntotal_cost > budget) continue;
            if (visited[npos] <= nmax_cost) continue;
            pq.push({nmax_cost, {npos, ntotal_cost}});
            visited[npos] = nmax_cost;
        }
    }
    return (visited[dest] == INF) ? -1 : visited[dest];
}

int main(){
    cin>>node_cnt>>edge_cnt>>start>>dest>>budget;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    cout<<dijkstra();
}