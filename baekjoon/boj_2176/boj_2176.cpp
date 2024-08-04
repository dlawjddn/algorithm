/**
 * @file boj_2176.cpp
 * @brief 백준 gold2 합리적인 이동경로
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

#define INF 2147483646
using namespace std;

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> visited;
vector<int> dp;

int dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 2});
    visited[2] = 0;
    dp[2] = 1;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] < cost) continue;
        for(int x = 0; x < maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] > ncost) {
                pq.push({ncost, npos});
                visited[npos] = ncost;
            }
            if (cost > visited[npos]) {
                dp[pos] += dp[npos];
            }
        }
    }
    return dp[1];
}

int main(){
    cin >> node_cnt >> edge_cnt;
    maps.resize(node_cnt + 1);
    dp.resize(node_cnt + 1, 0);
    visited.resize(node_cnt + 1, INF);
    for(int i = 0; i < edge_cnt; i++) {
        int node1, node2, cost;
        cin >> node1 >> node2 >> cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    cout << dijkstra();
}
