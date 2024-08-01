/**
 * @file boj_22865.cpp
 * @brief 백준 gold4 가장 먼 곳
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e18
using namespace std;

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<long long> visited;
priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;

void dijkstra() {
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            long long ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
    int answer = 0, max_len = 0;
    for(int i=1; i<=node_cnt; i++) {
        if (max_len < visited[i]) {
            max_len = visited[i];
            answer = i;
        }
    }
    cout<<answer;
}

int main(){
    cin>>node_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<3; i++) {
        int friend_pos; cin>>friend_pos;
        pq.push({0, friend_pos});
        visited[friend_pos] = 0;
    }
    cin>>edge_cnt;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    dijkstra();
}