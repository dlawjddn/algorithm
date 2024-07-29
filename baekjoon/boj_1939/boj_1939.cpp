/**
 * @file boj_1939.cpp
 * @brief 백준 gold3 중량제한
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, max_weight = 0, start, dest, answer;
vector<vector<pair<int, int> > > maps;

bool bfs(int limit) {
    queue<int> q;
    vector<bool> visited(node_cnt + 1, false);
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        if (pos == dest) return true;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            if (visited[npos] || limit > maps[pos][x].second) continue;
            q.push(npos);
            visited[npos] = true;
        }
    }
    return false;
}

void solve() {
    int left = 0, right = max_weight;
    while(left <= right) {
        int mid = (left + right) / 2;
        if (bfs(mid)) {
            left = mid + 1;
        } else right = mid - 1;
    }
    cout<<right;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, weight; cin>>node1>>node2>>weight;
        maps[node1].push_back(make_pair(node2, weight));
        maps[node2].push_back(make_pair(node1, weight));
        max_weight = max(max_weight, weight);
    }
    cin>>start>>dest;
    solve();
}