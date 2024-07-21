/**
 * @file boj_12893.cpp
 * @brief 백준 gold4 적의 적
 * @version 0.1
 * @date 2024-07-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;
vector<bool> check;
vector<bool> visited;

void bfs(int spos) {
    queue<int> q;
    q.push(spos);
    visited[spos] = true;
    check[spos] = true;
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            if (visited[npos]) continue;
            q.push(npos);
            check[npos] = !check[pos];
            visited[npos] = true;
        }
    }
}

bool binary_graph() {
    for(int i=1; i<=node_cnt; i++) {
        for(int j=0; j<maps[i].size(); j++) {
            if (check[i] == check[maps[i][j]]) return false;
        }
    }
    return true;
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    check.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, false);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    for(int i=1; i<=node_cnt; i++) {
        if (visited[i]) continue;
        bfs(i);
    }
    cout<<((binary_graph()) ? "1" : "0");
}