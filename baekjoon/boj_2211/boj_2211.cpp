/**
 * @file boj_2211.cpp
 * @brief 백준 gold2 네트워크 복구
 * @version 0.1
 * @date 2024-07-26
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

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> parents;
vector<int> visited;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, 1));
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
            parents[npos] = pos;
        }
    }
}

void solve() {
    cout<<node_cnt-1<<"\n";
    for(int i=2; i<=node_cnt; i++) cout<<i<<" "<<parents[i]<<"\n";
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt +1);
    parents.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    dijkstra();
    solve();
}