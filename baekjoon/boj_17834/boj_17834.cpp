/**
 * @file boj_17834.cpp
 * @brief 백준 gold1 사자와 토끼
 * @version 0.1
 * @date 2024-07-22
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

void dfs(int pos) {
    visited[pos] = true;
    for(int x=0; x<maps[pos].size(); x++) {
        int npos = maps[pos][x];
        if (visited[npos]) continue;
        check[npos] = !check[pos];
        dfs(npos);
    }
}

int solve() {
    int blue_cnt = 0, white_cnt = 0;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=0; j<maps[i].size(); j++) {
            if (check[i] == check[maps[i][j]]) return 0;
        }
    }
    for(int i=1; i<=node_cnt; i++) {
        if (check[i]) blue_cnt++;
        else white_cnt++;
    }
    return 2 * blue_cnt * white_cnt;
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
        check[i] = true;
        dfs(i);
    }
    cout<<solve();
}